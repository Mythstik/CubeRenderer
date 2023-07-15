#include <SDL2/SDL.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

SDL_Window* window;

float vertices[] = {
    -1, -1, -1,
    -1, -1, 1,
    -1, 1, -1,
    -1, 1, 1,
    1, -1, -1,
    1, -1, 1,
    1, 1, -1,
    1, 1, 1,
    -1, -1, -1,
    -1, -1, 1,
    1, -1, -1,
    1, -1, 1,
    -1, 1, -1,
    -1, 1, 1,
    1, 1, -1,
    1, 1, 1,
    -1, -1, -1,
    -1, 1, -1,
    1, -1, -1,
    1, 1, -1,
    -1, -1, 1,
    -1, 1, 1,
    1, -1, 1,
    1, 1, 1
};

float normals[] = {
    -1, -1, -1,
    -1, -1, 1,
    -1, 1, -1,
    -1, 1, 1,
    1, -1, -1,
    1, -1, 1,
    1, 1, -1,
    1, 1, 1,
    -1, -1, -1,
    -1, -1, 1,
    1, -1, -1,
    1, -1, 1,
    -1, 1, -1,
    -1, 1, 1,
    1, 1, -1,
    1, 1, 1,
    -1, -1, -1,
    -1, 1, -1,
    1, -1, -1,
    1, 1, -1,
    -1, -1, 1,
    -1, 1, 1,
    1, -1, 1,
    1, 1, 1
};

int indices[] = {
    0, 1, 3, 3, 2, 0,
    1, 5, 7, 7, 3, 1,
    5, 4, 6, 6, 7, 5,
    4, 0, 2, 2, 6, 4,
    2, 3, 7, 7, 6, 2,
    0, 4, 5, 5, 1, 0,
    8, 9, 11, 11, 10, 8,
    9, 13, 15, 15, 11, 9,
    13, 12, 14, 14, 15, 13,
    12, 8, 10, 10, 14, 12,
    10, 11, 15, 15, 14, 10,
    8, 12, 13, 13, 9, 8,
    16, 17, 19, 19, 18, 16,
    17, 21, 23, 23, 19, 17,
    21, 20, 22, 22, 23, 21,
    20, 16, 18, 18, 22, 20,
    18, 19, 23, 23, 22, 18,
    16, 20, 21, 21, 17, 16
};

void display() {
    glClearColor(0.529, 0.808, 0.922, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float angle = 0.0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);
    glRotatef(angle, 0, 1, 0);
    angle += 0.5;

    GLfloat material[] = { 1.0, 0.0, 0.8, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    SDL_GL_SwapWindow(window);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set the lighting properties
    GLfloat ambient_light[] = { 0.01, 0.01, 0.01, 1.0 };
    GLfloat diffuse_light[] = { 0.3, 0.3, 0.3, 0.0 };
    GLfloat light_position[] = { 3.5, 5.0, -12.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 800.0 / 600.0, 0.1, 100);

    SDL_Event event;
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        display();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
