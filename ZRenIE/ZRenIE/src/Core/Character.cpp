#include "Character.hpp"

#include "World.hpp"

#include "Traits/TModel.hpp"
#include "Traits/TColorMaterial.hpp"
#include "Traits/TTextureMaterial.hpp"

#include "Renderer.hpp"

Character::Character(const nlohmann::json& characterData)
	: ID(characterData["id"]), m_Name(characterData["name"]),
	m_TransformTrait(std::make_shared<TTransform>(characterData["transform"]))
{
}

void Character::Initialize(const nlohmann::json& characterData, std::shared_ptr<World> root)
{
	// Create and add all traits
	if (characterData.contains("modelFilePath"))
	{
		std::shared_ptr<TModel> model = std::make_shared<TModel>(characterData["modelFilePath"]);
		AddTrait(model);

		if (characterData.contains("material"))
		{
			nlohmann::json materialData = characterData["material"];

			std::shared_ptr<TMaterial> material;
			if (materialData["type"] == "TTextureMaterial")
				material = std::make_shared<TTextureMaterial>(materialData["textureFilePath"]);
			else if (materialData["type"] == "TColorMaterial")
				material = std::make_shared<TColorMaterial>(materialData["color"]);

			AddTrait(material);

			for (auto& mesh : model->m_Meshes)
			{
				mesh->m_Material = material;
			}
		}
	}

	m_Root = root;
	root->m_Characters.emplace(this->GetIdCopy(), shared_from_this());

	// Repeat process for all children
	for (auto& childCharacterData : characterData["children"])
	{
		std::shared_ptr<Character> character = std::make_shared<Character>(childCharacterData);
		RegisterChild(character);
		character->Initialize(childCharacterData, root);
	}
}

void Character::RegisterChild(std::shared_ptr<Character> child)
{
	m_Children.emplace(child->GetId(), child);
	child->m_Parent = weak_from_this();

	child->m_TransformTrait->SetGlobalTransformProperties(m_TransformTrait->GetGlobalTransformProperties());
}

Character::~Character()
{
}

void Character::Update()
{
	//m_TransformTrait.Update();
	for (auto& trait : m_Traits)
	{
		// TODO: Do smth
	}
	updateChildren();
}

void Character::Render(std::shared_ptr<Renderer> renderer)
{
	renderer->Render(shared_from_this());

	renderChildren(renderer);
}

void Character::AddChild(std::shared_ptr<Character> child)
{
	// remove child from parent's collection
	if (auto oldParent = child->m_Parent.lock())
	{
		if (oldParent->m_Children.find(child->GetId())
			!= oldParent->m_Children.end())
		{
			size_t result = oldParent->m_Children.erase(child->GetId());
			if (result == 0)
			{
				Utils::logError("Unable to 'erase' (remove) child from collection!");
				return;
			}
		}
		else
		{
			Utils::logError("Invalid game object identifier: Trying to remove a child that is not present in the parent's children!");
			return;
		}
	}
	else
	{
		Utils::logError("Child's parent is invalid!");
		return;
	}

	// set parent of child to 'this'
	child->m_Parent = weak_from_this();

	// add to current collection
	m_Children.emplace(child->GetId(), child);


	// adjust the local position of the child to be:
	// child_global - this_global
	TransformProperties result = 
		child->m_TransformTrait->GetGlobalTransformPropertiesCopy()
		- m_TransformTrait->GetGlobalTransformPropertiesCopy();
	child->m_TransformTrait->SetLocalTransformProperties(result);
}

void Character::AddTrait(const std::shared_ptr<Trait>& newTrait)
{
	m_Traits.push_back(newTrait);
}

const std::string Character::GetIdCopy() const
{
	return ID;
}

const std::string& Character::GetId() const
{
	return ID;
}

void Character::updateChildren()
{
	for (auto element = m_Children.begin(); element != m_Children.end(); element++)
	{
		element->second->Update();
	}
}

void Character::renderChildren(std::shared_ptr<Renderer> renderer)
{
	for (auto element = m_Children.begin(); element != m_Children.end(); element++)
	{
		element->second->Render(renderer);
	}
}