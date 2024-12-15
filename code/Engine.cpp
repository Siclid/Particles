#include "Engine.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

// call the create member function to render the window and populate our m_window object
 Engine::Engine() {
	 m_Window.create(VideoMode::getDesktopMode(), "screen", Style::Default); // initializes the window with the dimensions, title, and additional style settings

}

 void Engine::run() {
	 srand(static_cast<unsigned int>(time(0)));
	 Clock clock; // tracks the elapsed

	 // Create a local particle for unit tests
	 Particle lp(m_Window, 4, { static_cast<int>(m_Window.getSize().x / 2), static_cast<int>(m_Window.getSize().y / 2) });
	 lp.unitTests();
	 cout << "Unit tests complete. Starting Engine..." << endl;

	 while (m_Window.isOpen()) { // open up the window 
		 Time dt = clock.restart();
		 float dtSecs = dt.asSeconds();

		 input();
		 update(dtSecs); // updating the time differential here!
		 draw();
	 } 
 }

 void Engine::input() {
	 Event event;
	 while (m_Window.pollEvent(event)) {
		 if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
			 m_Window.close(); // Close window if 'Esc' is pressed or window is closed
		 }

		 if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			 Vector2i mousePosition = Mouse::getPosition(m_Window);
			 for (int i = 0; i < 5; i++) {
				 int numberOfPoints = 25 + rand() % 26; // Randomized number of points
				 m_particles.emplace_back(m_Window, numberOfPoints, mousePosition); // Use Vector2i directly
			 }
		 }
	 }
 }

 void Engine::update(float dtAsSeconds) {
	 for (auto i = m_particles.begin(); i != m_particles.end();) {
        if (i->getTTL() > 0.0f) {
            i->update(dtAsSeconds);
            ++i; 
        } else {
            i = m_particles.erase(i);
        }
    }
}

 void Engine::draw() {
	 m_Window.clear(Color::Black);
	 for (const auto& particle : m_particles) {
		 m_Window.draw(particle);
	 }
	 m_Window.display(); // display the window state. or updated window frame.
 }


