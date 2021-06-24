#ifndef BALL_H
#define BALL_H
#include "Brick.cpp"
#include "Paddle.cpp"
// #include "physics.h"

struct Ball : public sf::CircleShape
{
	// Constructor
	Ball(b2World& world, float x, float y, float r, float s, float a, bool texture, b2BodyType type = b2_dynamicBody)
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
		// this->setFillColor(sf::Color::White);
		if (texture)
		{
			ball_txt.loadFromFile("content/ball.png");
			this->setTexture(&ball_txt);
		}
		else
		{
			this->setFillColor(sf::Color::White);
		}
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
	bool checkCollision(const Paddle& p1, bool wall, bool left) // Calls the memory address instead of copying
	{
		for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
		{
			if (edge->other == p1.body)
			{
				if (edge->contact->IsTouching())
				{
					// Bounce ball off paddle and walls
					if (wall)
					{
						if (left)
						{
							angle = 45;
						}
						else
						{
							angle = 135;
						}
						body->SetLinearVelocity(b2Vec2(20 * cos(angle / deg_per_rad), 20 * sin(angle / deg_per_rad)));
					}
					else
					{
						angle = (this->getPosition().x - p1.getPosition().x) / (p1.getSize().x / 2) * 70 - 90;
						body->SetLinearVelocity(b2Vec2(20 * cos(angle / deg_per_rad), 20 * sin(angle / deg_per_rad)));
					}
					return true;
				}
			}
		}
		return false;
	}

	// when the ball hits the side walls make the ball bounce a certain way kinda like the trump game

	// Collision with ball and floor for death
	bool deathCollision(b2World& world, sf::RenderWindow& window, const Paddle& barrier, int& powerup, Ball& b1, Paddle& p1, std::vector<Brick>& bricks, int dif) // Calls the memory address instead of copying
	{
		for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
		{
			if (edge->other == barrier.body)
			{
				if (edge->contact->IsTouching())
				{
					powerup = 0;
					world.DestroyBody(p1.body);
					Paddle holder(world, window.getSize().x / 2 - 50, window.getSize().y * 0.9, window.getSize().x / 12, window.getSize().y / 67.5);
					p1 = holder;
					world.DestroyBody(b1.body);
					int r = (window.getSize().x / 30) / 2;
					speed = 250 * dif;
					angle = 90;
					b2BodyDef bodyDef;
					bodyDef.position.Set((window.getSize().x / 2) / pixels_per_meter, 300 / pixels_per_meter);
					bodyDef.type = b2_dynamicBody;
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

					// Read about the this operator
					this->setRadius(r);
					this->setOrigin(r, r);
					this->setPosition(200, 300);
					this->setFillColor(sf::Color::White);
					body->SetLinearVelocity(b2Vec2(speed / pixels_per_meter * cos(angle / deg_per_rad), speed / pixels_per_meter * sin(angle / deg_per_rad)));
					for (long unsigned int i = 0; i < bricks.size(); i++)
					{
						world.DestroyBody(bricks[i].body);
					}
					bricks.clear();
					bricks[0].refill_vector(world, window, dif, bricks);
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
	void resize(b2World& world, sf::RenderWindow& window, int dif, Paddle p1)
	{
		// angle = this->body->GetAngle(); // Results in a bug of the ball stuck bouncing from wall to wall
		angle = 90;
		// By allowing x to be the paddle position it resolves the bug of the ball being outside of the resized window after resizing
		int x = p1.getPosition().x + p1.getSize().x / 2, y = window.getSize().y / 3, r = (window.getSize().x / 30) / 2;
		world.DestroyBody(this->body);
		speed = 250 * dif;
		b2BodyDef bodyDef;
		bodyDef.position.Set(x / pixels_per_meter, y / pixels_per_meter);
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 0.0;
		b2CircleShape b2shape;

		b2shape.m_radius = r / pixels_per_meter; // also need to fix the death collison to follow this standard of radius sizing

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.0;
		fixtureDef.restitution = 1.0;
		fixtureDef.shape = &b2shape;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		// Read about the this operator
		this->setRadius(r);
		this->setOrigin(r, r);
		this->setPosition(x, y);
		// this->setFillColor(sf::Color::White);
		body->SetLinearVelocity(b2Vec2(speed / pixels_per_meter * cos(angle / deg_per_rad), speed / pixels_per_meter * sin(angle / deg_per_rad)));
	}
	void resize_in_game(b2World& world, sf::RenderWindow& window, int dif)
	{
		angle = this->body->GetAngle(); // Results in a bug of the ball stuck bouncing from wall to wall
		// By allowing x to be the paddle position it resolves the bug of the ball being outside of the resized window after resizing
		int x = this->getPosition().x, y = getPosition().y, r = (window.getSize().x / 30) / 2;
		world.DestroyBody(this->body);
		speed = 250 * dif;
		b2BodyDef bodyDef;
		bodyDef.position.Set(x / pixels_per_meter, y / pixels_per_meter);
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 0.0;
		b2CircleShape b2shape;

		b2shape.m_radius = r / pixels_per_meter; // also need to fix the death collison to follow this standard of radius sizing

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.0;
		fixtureDef.restitution = 1.0;
		fixtureDef.shape = &b2shape;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		// Read about the this operator
		this->setRadius(r);
		this->setOrigin(r, r);
		this->setPosition(x, y);
		// this->setFillColor(sf::Color::White);
		body->SetLinearVelocity(b2Vec2(speed / pixels_per_meter * cos(angle / deg_per_rad), speed / pixels_per_meter * sin(angle / deg_per_rad)));
	}
	// powerup that makes the balls linear velocity slower than usual
	void slow()
	{
		speed = 250;
	}
	// powerup that makes the ball big
	void big_ball(b2World& world, int dif, int r, float angle)
	{
		// angle = this->body->GetAngle(); // Results in a bug of the ball stuck bouncing from wall to wall
		int x = this->getPosition().x, y = this->getPosition().y;
		world.DestroyBody(this->body);
		speed = 250 * dif;
		b2BodyDef bodyDef;
		bodyDef.position.Set(x / pixels_per_meter, y / pixels_per_meter);
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 0.0;
		b2CircleShape b2shape;

		b2shape.m_radius = r / pixels_per_meter; // also need to fix the death collison to follow this standard of radius sizing

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.0;
		fixtureDef.restitution = 1.0;
		fixtureDef.shape = &b2shape;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		// Read about the this operator
		this->setRadius(r);
		this->setOrigin(r, r);
		this->setPosition(x, y);
		// this->setFillColor(sf::Color::White);
		body->SetLinearVelocity(b2Vec2(speed / pixels_per_meter * cos(angle / deg_per_rad), speed / pixels_per_meter * sin(angle / deg_per_rad)));
	}
	void no_death(bool dead)
	{
		death = dead;
	}
	// member variables
	float speed, angle;
	bool death = false;
	b2Body* body; // box2d body
	sf::Texture ball_txt;
};

#endif