#ifndef BRICK_H
#define BRICK_H
#include "physics.h"

struct Brick : public sf::RectangleShape
{
	Brick(b2World& world, float x, float y, float width, float height)
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
	void updatePosition(sf::RenderWindow& render)
	{
		this->setPosition(body->GetPosition().x * pixels_per_meter, body->GetPosition().y * pixels_per_meter);
		this->setRotation(body->GetAngle() * deg_per_rad);
		render.draw(*this);
	}
	void refill_vector(b2World& world, int& dif, std::vector<Brick>& bricks)
	{
		// Could make a vector for each row and that row then has a diffrent dificulty to break (e.g. two hits, three hits)
		switch (dif)
		{
			case 1:
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 1; j++)
					{
						bricks.push_back(Brick(world, 40 + i * 120, 40 + j * 30, 60, 20));
						bricks.back().setFillColor(sf::Color::Cyan);
					}
				}
				break;
			case 2:
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						bricks.push_back(Brick(world, 40 + i * 120, 40 + j * 30, 60, 20));
						bricks.back().setFillColor(sf::Color::Cyan);
						// physics::setCollisionID(bricks.back().body, -1); // try and get to smash through the bricks
					}
				}
				break;
			case 3:
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						bricks.push_back(Brick(world, 40 + i * 120, 40 + j * 30, 60, 20));
						bricks.back().setFillColor(sf::Color::Cyan);
					}
				}
				break;
			default:
				break;
		}
	}

	b2Body* body;
};

#endif