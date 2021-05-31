#ifndef BALL_H
#define BALL_H
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

		sf::CircleShape* shape1 = new sf::CircleShape(r);
		shape1->setOrigin(r, r);
		shape1->setPosition(x, y);
		shape1->setFillColor(sf::Color::White);

		body->SetUserData(shape1);
		body->SetLinearVelocity(b2Vec2(speed / pixels_per_meter * cos(angle / deg_per_rad), speed / pixels_per_meter * sin(angle / deg_per_rad)));
	}
	void updatePosition()
	{
		// Limit velocity
		b2Vec2 velocity = body->GetLinearVelocity();
		body->SetLinearVelocity((speed / pixels_per_meter) / velocity.Length() * velocity);
	}
	// member variables
	float speed, angle;
	b2Body* body; // box2d body
};

#endif