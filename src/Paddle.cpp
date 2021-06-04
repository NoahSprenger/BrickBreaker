#ifndef PADDLE_H
#define PADDLE_H
#include "physics.h"

struct Paddle : public sf::RectangleShape
{
	Paddle(b2World& world, float x, float y, float width, float height)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set((x + width / 2.0) / pixels_per_meter, (y + height / 2.0) / pixels_per_meter);
		bodyDef.type = b2_kinematicBody;
		bodyDef.linearDamping = 0.05;
		b2PolygonShape b2shape;
		b2shape.SetAsBox(width / pixels_per_meter / 2.0, height / pixels_per_meter / 2.0);
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.0;
		fixtureDef.restitution = 1.0;
		fixtureDef.shape = &b2shape;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		// sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(width, height));
		this->setSize(sf::Vector2f(width, height));
		this->setOrigin(width / 2.0, height / 2.0);
		this->setPosition(x, y);
		this->setFillColor(sf::Color::White);
		// body->SetUserData(shape);
	}
	void updatePosition(sf::RenderWindow& window)
	{
		//	Setting paddle velocity
		body->SetLinearVelocity(b2Vec2(0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			body->SetLinearVelocity(b2Vec2(-10, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			body->SetLinearVelocity(b2Vec2(10, 0));
		if (body->GetPosition().x * 32 > window.getSize().x)
			body->SetLinearVelocity(b2Vec2(-10, 0));
		if (body->GetPosition().x * 32 < 0)
			body->SetLinearVelocity(b2Vec2(10, 0));
		this->setPosition(body->GetPosition().x * pixels_per_meter, body->GetPosition().y * pixels_per_meter);
		this->setRotation(body->GetAngle() * deg_per_rad);
		window.draw(*this);
	}
	b2Body* body;
};

#endif