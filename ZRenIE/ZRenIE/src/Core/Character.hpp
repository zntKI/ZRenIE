#pragma once

#include "Traits/Trait.hpp"
#include "Traits/TTransform.hpp"

#include <nlohmann/json.hpp>

#include <string>
#include <map>
#include <vector>
#include <memory>

class Renderer;

class Character : public std::enable_shared_from_this<Character>
{
	friend class Renderer;

private:
	std::string identifier;

protected:
	std::weak_ptr<Character> m_Parent;
	std::vector<std::shared_ptr<Character>> m_Children;

	std::shared_ptr<TTransform> m_TransformTrait;
	std::vector<std::shared_ptr<Trait>> m_Traits;

public:
	Character(const nlohmann::json& characterData);
	void Initialize(const nlohmann::json& characterData);
	void RegisterChild(const std::shared_ptr<Character>& child);

	~Character();

	virtual void Update();
	virtual void Render(std::shared_ptr<Renderer> renderer);

	void AddChild(const std::shared_ptr<Character>& child);

	void AddTrait(const std::shared_ptr<Trait>& newTrait);

protected:
	void updateChildren();
	void renderChildren(std::shared_ptr<Renderer> renderer);
};