#pragma once
#include <vector>
#include <bitset>

const unsigned int MAX_COMPONENTS = 32;

// We use a bitset (1-0)s to keep track of which components an entity has,
// and also helps keep track of which entities a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
	static int nextId;
};

template<typename T>
class Component : public IComponent
{
	// Returns the unique id of Component<T>.
	static int GetId() {
		static int id = nextId++;
		return id;
	}
};

class Entity {

public:
	Entity(int id);

	Entity(const Entity& otherEntity) = default;

public:
	int GetId() const { return id; }
private:
	int id;

public:
	Entity& operator=(const Entity& other) = default;

	bool operator==(const Entity& other) const {
		return GetId() == other.GetId();
	}
	bool operator!=(const Entity& other) const {
		return GetId() != other.GetId();
	}
};

/*
* System
*
* The system process entities that contain specific signature.
*/
class System {

public:
	System() = default;
	~System() = default;

public:
	// Define the component type T that entities must have to be 
	// considered by the system.
	template<typename TComponent>
	void RequireComponent();
public:
	void AddEntityToSystem(Entity entity);

	void RemoveEntityFromSystem(Entity entity);

	std::vector<Entity> GetSystemEntities() const { return entities; }

private:
	std::vector<Entity> entities;

public:
	Signature GetSignature() const { return componentSignature; }
private:
	Signature componentSignature;

};

template<typename TComponent>
void System::RequireComponent() {

	const int componentId = Component<TComponent>().GetId();

	componentSignature.set(componentId);
}

class Registry {

};

