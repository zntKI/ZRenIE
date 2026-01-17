#include "Character.hpp"

#include "Traits/TModel.hpp"
#include "Traits/TColorMaterial.hpp"
#include "Traits/TTextureMaterial.hpp"

#include "Renderer.hpp"

void Character::updateChildren()
{
	for (auto& child : m_Children)
	{
		child->Update();
	}
}

void Character::renderChildren(std::shared_ptr<Renderer> renderer)
{
	for (auto& child : m_Children)
	{
		child->Render(renderer);
	}
}

Character::Character(const nlohmann::json& characterData)
	: identifier(characterData["identifier"]),
	m_TransformTrait(std::make_shared<TTransform>(characterData["transform"]))
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

	// Repeat process for all children
	for (auto& childCharacterData : characterData["children"])
	{
		std::shared_ptr<Character> character = std::make_shared<Character>(childCharacterData);
		AddChild(character);
	}
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

void Character::AddChild(const std::shared_ptr<Character>& child)
{
	m_Children.push_back(child);
	child->m_Parent = weak_from_this();
}

void Character::AddTrait(const std::shared_ptr<Trait>& newTrait)
{
	m_Traits.push_back(newTrait);
}