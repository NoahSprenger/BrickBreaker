#ifndef BALL_H
#define BALL_H
#include "Brick.cpp"
#include "Paddle.cpp"
#include "physics.h"

struct Ball : public sf::CircleShape
{
	// Constructor
	Ball(b2World& world, float x, float y, float r, float s, float a, b2BodyType type = b2_dynamicBody)
	{
		speed = s;
		angle = a;
		b2BodyDef bodyDef;
		bodyDef.position.Set(x / pixels_per_meter, y / pixels_per_meter);
		bodyDef.type = type;
		bodyDef.linearDamping = 0.0;
		b2CircleShape b2shape;

		b2shape.m_radius = r / pixels_per_meter;

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.0;
		fixtureDef.restitution = 1.0;
		fixtureDef.shape = &b2shape;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		// sf::CircleShape* shape1 = new sf::CircleShape(r);
		// Read about the this operator
		this->setRadius(r);
		this->setOrigin(r, r);
		this->setPosition(x, y);
		this->setFillColor(sf::Color::White);

		// body->SetUserData(this);
		body->SetLinearVelocity(b2Vec2(speed / pixels_per_meter * cos(angle / deg_per_rad), speed / pixels_per_meter * sin(angle / deg_per_rad)));
	}
	void updatePosition(sf::RenderWindow& render)
	{
		// Limit velocity
		b2Vec2 velocity = body->GetLinearVelocity();
		body->SetLinearVelocity((speed / pixels_per_meter) / velocity.Length() * velocity);
		this->setPosition(body->GetPosition().x * pixels_per_meter, body->GetPosition().y * pixels_per_meter);
		this->setRotation(body->GetAngle() * deg_per_rad);
		render.draw(*this);
	}
	// Collision with paddle and ball
	bool checkCollision(const Paddle& p1) // Calls the memory address instead of copying
	{
		for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
		{
			if (edge->other == p1.body)
			{
				if (edge->contact->IsTouching())
				{
					// Bounce ball of paddle
					angle = (this->getPosition().x - p1.getPosition().x) / (p1.getSize().x / 2) * 70 - 90;
					body->SetLinearVelocity(b2Vec2(20 * cos(angle / deg_per_rad), 20 * sin(angle / deg_per_rad)));
					return true;
				}
			}
		}
		return false;
	}
	// Collision with brick
	bool checkCollision(const Brick& b1) // Calls the memory address instead of copying
	{
		for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
		{
			if (edge->other == b1.body)
			{
				if (edge->contact->IsTouching())
				{
					return true;
				}
			}
		}
		return false;
	}
	// member variables
	float speed, angle;
	b2Body* body; // box2d body
};

#endif