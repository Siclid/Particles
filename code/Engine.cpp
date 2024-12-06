#include "Engine.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace sf;

// call the create member function to render the window and populate our m_window object
 Engine::Engine() {
	 m_Window.create(VideoMode::getDesktopMode(), "screen", Style::Default); // initializes the window with the dimensions, title, and additional style settings

}

 void Engine::run() {
	 Clock clock; // obviously tracks the elapsed time
	 Time time;

	 Particle lp(m_Window, 4, {
		 (int)m_Window.getSize().x / 2,
		 (int)m_Window.getSize().y / 2
		 }); // the local particle that is being sized based on the window renderTarget and unit tests

	 lp.unitTests();
	 
	 cout << "Unit tests complete. Starting Engine..." << endl;

	 while (m_Window.isOpen()) // open up the window
	 {
		 Time dt = clock.restart();
		 float dtSecs = dt.asSeconds();

		 input();
		 update(dtSecs); // updating the time differential here!
		 draw();
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
	 m_Window.clear(Color::Magenta);
	 for (const auto& particle : m_particles) {
		 m_Window.draw(particle);
	 }
	 m_Window.display(); // display the window state. or updated window frame.
 }

 void Engine::input() {
	 Event event;
	 while (m_Window.pollEvent(event)) {
		 if (event.type == Event::Closed) {
			 m_Window.close(); // setup close event
		 }

		 if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
			 m_Window.close(); // setup escape key close :D
		 }

		 if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			 // get the mouse click position
			 Vector2i mousePosition = Mouse::getPosition(m_Window);

			 // generate numbers according to professors range of [25,50] 
			 for (int i = 0; i < 5; i++) {
				 int numberOfPoints = 25 + rand() % 26; // range from 0 to 25
				 m_particles.emplace_back(m_Window, numberOfPoints, mousePosition);
			 }


		 }

	 }
 }
