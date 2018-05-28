#pragma once

class UIElement;
class UIFont;

#include <vector>
#include <map>
#include <glm\glm.hpp>
#include <functional>
#include <fmod.hpp>

#include "UIElement.h"

#define BLACK	glm::vec4(0.f/255.f,	0.f/255.f,		0.f/255.f,		255.f/255.f)
#define BLUE	glm::vec4(30.0f/255.f,	167.f/255.f,	225.f/255.f,	255.f/255.f)
#define GREEN	glm::vec4(136.f/255.f,	224.f/255.f,	96.f/255.f,		255.f/255.f)
#define GREY	glm::vec4(238.f/255.f,	238.f/255.f,	238.f/255.f,	255.f/255.f)
#define ORANGE	glm::vec4(250.f/255.f,	129.f/255.f,	50.f/255.f,		255.f/255.f)
#define	WHITE	glm::vec4(255.f/255.f,	255.f/255.f,	255.f/255.f,	255.f/255.f)
#define	YELLOW	glm::vec4(255.f/255.f,	217.f/255.f,	72.f/255.f,		255.f/255.f)

class UIManager
{
public:
	UIManager(void);
	~UIManager(void);
	
	void Update();
	void Draw();
	
	void MakePanel		(glm::vec2 Position, glm::vec2 Dimensions, TransitionType Type, float TotalTime, float DisplacementAmount, float * ReferenceForText, wchar_t * Text = nullptr, glm::vec4 Colour = glm::vec4(1));
	void MakeButton		(glm::vec2 Position, glm::vec2 Dimensions, TransitionType Type, float TotalTime, float DisplacementAmount, wchar_t * Text = nullptr, std::function<void()> CallBackFunction = nullptr, glm::vec4 NormalColour = glm::vec4(1), glm::vec4 HoverColour = glm::vec4(1), glm::vec4 PressedColour = glm::vec4(1));
	void MakeTickBox	(glm::vec2 Position, glm::vec2 Dimensions, TransitionType Type, float TotalTime, float DisplacementAmount, bool * CallBackBoolean);
	void MakeSlider		(glm::vec2 Position, glm::vec2 Dimensions, TransitionType Type, float TotalTime, float DisplacementAmount, float * CallBackFloat, float MinValue, float MaxValue);
	void MakeDropDownBox(glm::vec2 Position, glm::vec2 Dimensions, TransitionType Type, float TotalTime, float DisplacementAmount, std::vector<wchar_t *> ChoiceList, unsigned int * DefaultChoice);

	static void DrawString(wchar_t * Text, glm::vec2 Position, glm::vec4 Colour = glm::vec4(0,0,0,1));

	void TransitionAll(TransitionType Type, float TotalTime, float DisplacementAmount = 0, std::function<void()> OnceCompleteFunction = nullptr);

	void AddUIElement(UIElement * Element);
	void ReverseElements();
	void ClearUIElements();
	static UIFont * m_font;

	static void drawFont();
	static void updateFont();
	static void updateAudio();

private:
	std::vector<UIElement *> m_elements;
	
	static std::map<const char *, unsigned int> * m_textureMap;
	static unsigned int m_uiShader;
	static unsigned int m_fontShader;
	static glm::mat4 orthoProjection;
	
	// static audio variables
	static FMOD::System * m_fmodSystem;
	static FMOD::Channel * m_fmodChannel;
	static FMOD::Sound * m_buttonSound;

	// Functions just to wrap code up into
	void LoadTextures();
	void LoadUIShader();
	void LoadFontShader();
	
	// Callback function once the current transition has completed
	bool m_transitionCalled;
	std::function<void()> m_callbackfunction;
	bool m_callBackCalled;
};

