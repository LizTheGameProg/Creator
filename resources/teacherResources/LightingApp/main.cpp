#include "LightingApp.h"
#include <GLFW/glfw3.h>

int main() {
	
	Application* app = new LightingApp();
	if (app->startup()) {

		double prevTime = glfwGetTime();
		double currTime = 0;

		while (currTime = glfwGetTime(),
			app->update((float)(currTime - prevTime))) {
			app->draw();
			prevTime = currTime;
		}
	}
	app->shutdown();

	return 0;
}