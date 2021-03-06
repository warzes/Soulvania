#include "stdafx.h"
#include "GameObject.h"
#include "MathHelper.h"
#include "CppExtensions.h"
#include "UpdateData.h"
#include "Settings.h"
#include "CollisionGrid.h"

GameObject::GameObject(ObjectId type) : body{ *this }
{
	this->objectId = type;
}

#pragma region Getters / Setters

ObjectId GameObject::GetId()
{
	return objectId;
}

int GameObject::GetType()
{
	return (int)objectId;
}

void GameObject::SetState(ObjectState state)
{
	this->state = state;
	SendMessageToSystems(STATE_CHANGED);
}

ObjectState GameObject::GetState()
{
	return state;
}

base::Vector2 GameObject::GetPosition()
{
	return position;
}

void GameObject::SetPosition(float x, float y)
{
	auto newPosition = base::Vector2{ x, y };

	if (collisionGrid != nullptr)
		collisionGrid->Move(*this, newPosition - position);
	else
		position = newPosition;
}

void GameObject::SetPosition(base::Vector2 position)
{
	SetPosition(position.x, position.y);
}

void GameObject::SetRawPosition(base::Vector2 position)
{
	this->position = position;
}

base::Vector2 GameObject::GetDistance()
{
	if (movementSystem != nullptr)
		return movementSystem->GetDistance();

	return base::Vector2::Zero();
}

void GameObject::SetDistance(base::Vector2 distance)
{
	if (movementSystem != nullptr)
		return movementSystem->SetDistance(distance);
}

void GameObject::SetDistance_X(float value)
{
	SetDistance(base::Vector2{ value, GetDistance().y });
}

void GameObject::SetDistance_Y(float value)
{
	SetDistance(base::Vector2{ GetDistance().x, value });
}

base::Vector2 GameObject::GetOriginPosition()
{
	return base::Vector2{
		position.x + GetFrameRect().Width() / 2,
		position.y + GetFrameRect().Height() / 2 };
}

void GameObject::SetOriginPosition(base::Vector2 value)
{
	SetPosition(base::Vector2{
		value.x - GetFrameRect().Width() / 2,
		value.y - GetFrameRect().Height() / 2 });
}

base::Vector2 GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetVelocity(base::Vector2 velocity)
{
	this->velocity = velocity;
}

void GameObject::SetVelocity_X(float x)
{
	velocity.x = x;
}

void GameObject::SetVelocity_Y(float y)
{
	velocity.y = y;
}

void GameObject::SetDirection(float angle)
{
	// The X-Y axis in game has the value Y inverted compare to the X-Y axis in math
	// To convert the X-Y axis from math to game, we need to flip the degrees sign because
	//   with sin(θ) = y, sin(-θ) = -y
	//   with cos(θ) = x, cos(θ) = x
	auto direction = MathHelper::Degrees2Vector(-angle);
	SetDirection(direction);
}

void GameObject::SetDirection(base::Vector2 direction)
{
	velocity = direction * speed;
}

float GameObject::GetSpeed()
{
	return speed;
}

void GameObject::SetSpeed(float speed)
{
	this->speed = speed;
}

RectF GameObject::GetFrameRect()
{
	if (GetSprite() == nullptr)
		return RectF::Empty();

	return GetSprite()->GetFrameRectangle(position);
}

RectF GameObject::GetBoundingBox()
{
	if (GetSprite() == nullptr)
		return RectF::Empty();

	return GetSprite()->GetBoundingRectangle(position);
}

Sprite* GameObject::GetSprite()
{
	if (renderingSystem != nullptr)
		return &renderingSystem->GetSprite();
	else
		return nullptr;
}

Facing GameObject::GetFacing()
{
	return facing;
}

void GameObject::SetFacing(Facing facing)
{
	this->facing = facing;
	SendMessageToSystems(FACING_CHANGED);

	if (GetSprite() == nullptr)
		return;

	if (facing == Facing::Left)
		GetSprite()->SetEffect(SpriteEffects::FlipHorizontally);
	else
		GetSprite()->SetEffect(SpriteEffects::None);
}

void GameObject::SetVisibility(bool value)
{
	if (GetSprite() == nullptr)
		return;

	GetSprite()->SetVisibility(value);
}

Body& GameObject::GetBody()
{
	return body;
}

void GameObject::Destroy()
{
	state = ObjectState::DEAD;
}

void GameObject::EnableControl(bool value)
{
	if (controlSystem != nullptr)
		controlSystem->Enabled(value);
}

void GameObject::EnableMovement(bool value)
{
	movementSystem->Enabled(value);
}

void GameObject::Move(base::Vector2 distance)
{
	if (distance == base::Vector2::Zero())
		return;

	if (collisionGrid != nullptr)
		collisionGrid->Move(*this, distance);
	else
		position += distance;
}

void GameObject::SwitchFacing()
{
	if (facing == Facing::Left)
		SetFacing(Facing::Right);
	else if (facing == Facing::Right)
		SetFacing(Facing::Left);
}

CollisionGridData GameObject::GetCollisionGridData()
{
	return collisionGridData;
}

void GameObject::SetCollisionGridData(CollisionGridData data)
{
	collisionGridData = data;
}

void GameObject::Attach(CollisionGrid* grid)
{
	collisionGrid = grid;
}

void GameObject::Attach(std::unique_ptr<IControlSystem> system)
{
	components.push_back(system.get());
	controlSystem = std::move(system);
}

void GameObject::Attach(std::unique_ptr<IMovementSystem> system)
{
	components.push_back(system.get());
	movementSystem = std::move(system);
}

void GameObject::Attach(std::unique_ptr<ICollisionSystem> system)
{
	components.push_back(system.get());
	collisionSystem = std::move(system);
}

void GameObject::Attach(std::unique_ptr<ICollisionResponseSystem> system)
{
	components.push_back(system.get());
	collisionResponseSystem = std::move(system);
}

void GameObject::Attach(std::unique_ptr<IRenderingSystem> system)
{
	components.push_back(system.get());
	renderingSystem = std::move(system);
}

template<>
void GameObject::Detach<IControlSystem>()
{
	RemoveByValue(components, controlSystem.get());
	controlSystem = nullptr;
}

template<>
void GameObject::Detach<IMovementSystem>()
{
	RemoveByValue(components, movementSystem.get());
	movementSystem = nullptr;
}

template<>
void GameObject::Detach<ICollisionSystem>()
{
	RemoveByValue(components, collisionSystem.get());
	collisionSystem = nullptr;
}

template<>
void GameObject::Detach<ICollisionResponseSystem>()
{
	RemoveByValue(components, collisionResponseSystem.get());
	collisionResponseSystem = nullptr;
}

template<>
void GameObject::Detach<IRenderingSystem>()
{
	RemoveByValue(components, renderingSystem.get());
	renderingSystem = nullptr;
}

#pragma endregion

void GameObject::LoadContent(ContentManager& content)
{
	if (renderingSystem != nullptr)
		renderingSystem->LoadContent(content);
}

void GameObject::Update(UpdateData& updateData)
{
	auto collisionObjects = updateData.collisionObjects;

	if (controlSystem != nullptr)
		controlSystem->Update(updateData);

	if (movementSystem != nullptr)
		movementSystem->Update(updateData.gameTime);

	if (collisionSystem != nullptr && collisionObjects != nullptr)
		collisionSystem->Update(updateData);

	if (collisionResponseSystem != nullptr && collisionObjects != nullptr)
		collisionResponseSystem->Update(updateData);

	if (renderingSystem != nullptr)
		renderingSystem->Update(updateData.gameTime);

	Move(GetDistance()); // Can move properly now after handling potential collisions with other objects
}

void GameObject::Draw(SpriteExtensions& spriteBatch)
{
	if (renderingSystem != nullptr)
		renderingSystem->Draw(spriteBatch);
}

void GameObject::SendMessageToSystems(int message)
{
	for (auto& component : components)
	{
		component->Receive(message);
	}
}

GameObject& GameObject::NullObject()
{
	static auto nullGameObject = GameObject{ ObjectId::Unknown };
	return nullGameObject;
}

GameObject::~GameObject()
{
}