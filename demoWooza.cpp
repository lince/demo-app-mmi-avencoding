/*
 * main.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <string>
using namespace std;

#include "include/Puppet.h"
#include "include/SimpleScenario.h"
#include "include/Camera.h"
#include "include/EventHandler.h"
#include "include/Color.h"
using namespace ::br::ufscar::lince::xpta::demo;

#include <streaming/SharedBuffer.h>
#include <streaming/AVEncoder.h>
#include <streaming/RTPStream.h>
#include <streaming/UDPMpegTS.h>
#include <streaming/WowzaUDPInput.h>
#include <streaming/DeviceInterface.h>
#include <libffmpeg/libffmpeg.h>
using namespace ::br::ufscar::lince::streaming;

#include <cpputil/Thread.h>
using namespace cpputil;

class StreamGenerator : public Thread {
	void run();
};

void StreamGenerator::run() {
	FFMpeg_init();
	FFMpeg_setFramerate((char*) "24");
	FFMpeg_setFormat((char*) "shmgrab");
	FFMpeg_setInputFile((char*) ":0.0");
	FFMpeg_setVideoCodec((char*) "libx264");
	FFMpeg_setVideoPreset((char*) "default");
	FFMpeg_setVideoPreset((char*) "baseline");
	FFMpeg_setOther((char*) "g", (char*) "60");
	FFMpeg_setVideoBitrate((char*) "150000");
	FFMpeg_setAudioCodec((char*) "libaac");
	FFMpeg_setAudioBitrate((char*) "128000");
	FFMpeg_setAudioRate(48000);
	FFMpeg_setAudioChannels(2);
	FFMpeg_setVideoBsf((char*) "h264_mp4toannexb");
	FFMpeg_setFormat((char*) "mpegts");
	FFMpeg_setOutputFile((char*) "udp://200.18.98.27:10000?pkt_size=1316");
	FFMpeg_transcode();
}


//Objetos estáticos globais
Puppet* puppet;
Puppet* puppet2;
SimpleScenario* scenario;
Camera* camera;

int windowHeight, windowWidth;
unsigned char* bufferByte;
DeviceInterface* device;

//Definições das funções
static void draw();
static void animation(int parametro);
static void initStreaming();
void saveFrame();

//Implementaçõa das funções
void animation(int parametro) {
	puppet->move();
	//puppet2->move();
	glutPostRedisplay();
	glutTimerFunc(16, animation, 0);
}

void draw() {
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->point();
	puppet->draw();
	//puppet2->draw();
	scenario->draw();

	saveFrame();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 'c' || key == 'C') {
		camera->changeTypeUp();
	}
	glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			puppet->move(Puppet::TURNING_LEFT);
			break;
		case GLUT_KEY_RIGHT:
			puppet->move(Puppet::TURNING_RIGHT);
			break;
		case GLUT_KEY_UP:
			puppet->move(Puppet::WALKING);
			break;
		case GLUT_KEY_DOWN:
			puppet->move(GLPiece::GENERIC_MOVE);
			break;
	}
	//animation(0);
}

void saveFrame() {
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, bufferByte);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		cout<<"Erro ao salvar o frame."<<endl;
	}
	device->putBuffer2(bufferByte);
}

void initStreaming() {
	AVSource* source = new SharedBuffer();

	AVEncoder* encoder = new AVEncoder(source);
	encoder->setVideoCodec(H264);
	encoder->setVideoPreset("default");

	Streaming* streammer = new WowzaUDPInput("200.18.98.27", 5006); //verificar a porta
	//Streaming* streammer = new RTPStream(ipAdd, portNo);
	streammer->addStream(encoder);
	streammer->start();
}

/*
 ffmpeg -s 400  -re -vcodec libx264
 -vpre default -vpre baseline -g 60
 -vb 150000 -strict experimental -acodec aac
 -ab 128000 -ar 48000 -ac 2 -vbsf h264_mp4toannexb
 -f mpegts udp://200.18.98.27:10000?pkt_size=1316
*/


int main(int argc, char** argv) {

	windowHeight = 800;
	windowWidth = 800;

	//Inicia o Buffer Compartilhado
	device = DeviceInterface::getInstance();
	device->mount(windowWidth, windowHeight, 32, 25);
	bufferByte = new unsigned char[windowHeight*windowWidth*4];
	initStreaming();

	//Inicia Janela
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (windowWidth, windowHeight);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Demo XPTA-Streaming (Wooza)");

	//Seta forma do mundo
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,1,0.5,500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	////Inicializa os Objetos Gráficos
	puppet = new Puppet("Boneco1", 0.6, 0, 0);

	Color** pallet = new Color*[3];
	pallet[0] = (Color*) Color::SKIN_COLOR;
	pallet[1] = new Color("lightred", 0.65490,0.13333,0.16863);
	pallet[2] = new Color("darkred", 0.96471,0.78039,0.45490);
	//puppet2 = new Puppet("Boneco2", 0, 0, 0.7, pallet);
	scenario = new SimpleScenario("light_texture.raw");

	camera = new Camera(puppet);

	EventHandler* eventHandler = new EventHandler(puppet, camera);

	glutDisplayFunc(draw);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutTimerFunc(16, animation, 0);
	glutMainLoop();

	return EXIT_SUCCESS;
}
