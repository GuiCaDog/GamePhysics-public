#ifndef GP_GUI_SCENARIOCONTROL_H
#define GP_GUI_SCENARIOCONTROL_H

#include "Scenario.h"
#include <queue>
#include <nanogui/nanogui.h>
#include "common/messages/Message.h"
#include "common/messages/Queue.h"

struct GLFWwindow;

namespace gp
{

namespace gui
{

class ScenarioControl : public nanogui::Screen
{
private:
	/** The current scenario */
	gp::Scenario* m_scenario = nullptr;

	/** The next scenario (or null if the scenario should not change) */
	gp::Scenario* m_scenarioCandidate = nullptr;

	/** The pause button */
	nanogui::Button* m_playPause = nullptr;

	/** The next frame button */
	nanogui::Button* m_nextFrame = nullptr;

	/** <code>True</code> if the physics engine is paused */
	bool m_paused = false;

	/** The outgoing queue to the physics engine */
	gp::messages::Queue<gp::messages::Message>& m_vis2engine;

	/**
	 * Callback for the pause button
	 */
	void toggleEngine();

	/**
	 * Callback for the step button
	 */
	void stepEngine();

public:
	bool enableConstraintsRendering = true;
// 	gp::messages::Queue<gp::messages::Message> engineMessages;

	ScenarioControl(GLFWwindow* window, gp::messages::Queue<gp::messages::Message>& vis2engine);
	~ScenarioControl();

	gp::Scenario* peekScenario() const { return m_scenarioCandidate; }
	gp::Scenario* scenario() const { return m_scenario; }
	bool hasNewScenario() const { return m_scenarioCandidate != nullptr; }

	template<typename T>
	void loadScenario() { m_scenarioCandidate = new T; }
	void swapScenario();

	virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);

	bool interactsWithMouse();
};

}

}

#endif // GP_GUI_SCENARIOCONTROL_H
