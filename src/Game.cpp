#include <Game.h>

Game::Game() {}

Game::~Game() {}

Game::Game(const Game& src) {
	*this = src;
}

Game& Game::operator=(const Game& src)
{
	if (this != &src) {
	}
	return *this;
}


void Game::initGame() {
	_window = sf::RenderWindow(sf::VideoMode({800, 600}), "My window");

	_rectangle = sf::RectangleShape({_recWidth, _recHeight});
	_rectangle.setPosition({20.f, HEIGHT / 2.f - _recHeight / 2.f});
	_rectangle.setOutlineThickness(0.f);
	_rectangle.setFillColor(sf::Color::White);

	_ballSpeed = 600;
	_ball = sf::CircleShape(_ballSize);
	_ball.setPosition({WIDTH / 2.f, HEIGHT / 2.f});
	_ball.setOutlineThickness(0.f);
	_ball.setFillColor(sf::Color::White);
	_ball.setOrigin({_ballSize, _ballSize});
	_ball.setRotation(sf::degrees(40.f));
}

void Game::run() {

	while (_window.isOpen())
	{
		checkEvents();
		checkInputs();
		MoveBall();
		_dt = _clock.restart();

		for (auto particleEffect = _particlesEffects.rbegin(); particleEffect != _particlesEffects.rend();) {
			if (particleEffect->areAllParticlesDead())
				particleEffect = std::vector<ParticleSystem>::reverse_iterator(_particlesEffects.erase(std::next(particleEffect).base()));
			else
				++particleEffect;
		}

		_window.clear();
		_window.draw(_rectangle);
		_window.draw(_ball);
		for (auto &particleEffect : _particlesEffects) {
			particleEffect.update(_dt);
			_window.draw(particleEffect);
		}
		_window.display();
	}

}

void Game::checkEvents()
{
	while (const std::optional event = _window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			_window.close();
		if (const sf::Event::KeyPressed* keyPress = event->getIf<sf::Event::KeyPressed>())
			if (keyPress->scancode == sf::Keyboard::Scan::Escape)
				_window.close();
		if (event->getIf<sf::Event::MouseButtonReleased>())
			_particlesEffects.emplace_back(ParticleSystem(
				50,
				{_ball.getPosition().x, _ball.getPosition().y},
				sf::Color::White,
				{1, 1},
				{0.01f, 0.01f},
				0,
				360,
				sf::seconds(0.3f),
				{0, 0},
				0,
				0,
				0,
				false
			));
	}
}

void Game::checkInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && _rectangle.getPosition().y + _recHeight < HEIGHT)
	{
		_rectangle.move({0, 1.f * _moveSpeed * _dt.asSeconds()});
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && _rectangle.getPosition().y > 0)
	{
		_rectangle.move({0, -1.f * _moveSpeed * _dt.asSeconds()});
	}
	// _rectangle.rotate(sf::degrees((rand() % 201 - 100) / 100.f));
	// _rectangle.setOrigin({_rectangle.getOrigin().x + rand() % 3 - 1, _rectangle.getOrigin().y + rand() % 3 - 1});
}

void Game::MoveBall() {
	static std::random_device rd;
	static std::mt19937       rng(rd());

	float angle = _ball.getRotation().asRadians();
	sf::Vector2f	ballFacing = {cos(angle), sin(angle)};
	sf::Vector2f	ballTrajectory = {_ball.getPosition().x + ballFacing.x * _ballSpeed * _dt.asSeconds(), _ball.getPosition().y + ballFacing.y * _ballSpeed * _dt.asSeconds()};

	_particlesEffects.emplace_back(ParticleSystem(
		5,
		{std::uniform_real_distribution(_ball.getPosition().x - _ball.getRadius(), _ball.getPosition().x + _ball.getRadius())(rng),
			std::uniform_real_distribution(_ball.getPosition().y - _ball.getRadius(), _ball.getPosition().y + _ball.getRadius())(rng)},
		sf::Color::White,
		{1, 1},
		{50, 150},
		static_cast<int>(_ball.getRotation().asDegrees() - 180) % 360,
		45,
		sf::seconds(0.05f),
		{0, 0},
		0,
		0,
		1,
		false
	));

	if ((ballTrajectory.y <= 0 || ballTrajectory.y >= HEIGHT)
		|| (ballTrajectory.x <= 0 || ballTrajectory.x >= WIDTH))
		_particlesEffects.emplace_back(ParticleSystem(
			40,
			{_ball.getPosition().x, _ball.getPosition().y},
			sf::Color::White,
			{1, 1},
			{125, 125},
			0,
			360,
			sf::seconds(0.45f),
			{0, 0},
			0,
			0,
			0,
			false
	));

	if (ballTrajectory.y <= 0 || ballTrajectory.y >= HEIGHT)
		ballFacing.y *= -1;
	if (ballTrajectory.x <= 0 || ballTrajectory.x >= WIDTH)
		ballFacing.x *= -1;

	_ball.setRotation(sf::radians(std::atan2(ballFacing.y, ballFacing.x)));
	_ball.move({ballFacing.x * _ballSpeed * _dt.asSeconds(), ballFacing.y * _ballSpeed * _dt.asSeconds()});
}
