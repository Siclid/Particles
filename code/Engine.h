#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
    RenderWindow m_Window;
    vector<Particle> m_particles;
    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    Engine();
    void run();
};

#endif // ENGINE_H
