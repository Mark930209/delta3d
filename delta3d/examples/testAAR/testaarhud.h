/*
 * Delta3D Open Source Game and Simulation Engine
 * Copyright (C) 2005, BMH Associates, Inc.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Curtiss Murphy
 */
#ifndef DELTA_TEST_AAR_HUD
#define DELTA_TEST_AAR_HUD

#include <dtGame/message.h>
#include <dtGame/gmcomponent.h>
#include <osg/Referenced>

//This is for the CEGUI headers.
#ifdef None
#undef None
#endif
//#include <CEGUI/CEGUI.h>
#include <CEGUI/CEGUIWindow.h>
#include <dtGUI/ceuidrawable.h>
#include "export.h"

#define HUDCONTROLMAXTEXTSIZE 100

namespace dtCore
{
   class Keyboard;
   class Mouse;
}

namespace dtActors
{
   class TaskActorProxy;
}

namespace dtGame
{
   class ServerLoggerComponent;
   class LogController;
   class TaskComponent;
}

/**
 * HUD State enumeration - what info is the HUD showing.
 */
class TEST_AAR_EXPORT HUDState : public dtUtil::Enumeration
{
   DECLARE_ENUM(HUDState);
   public:
      static HUDState MINIMAL;
      static HUDState MEDIUM;
      static HUDState MAXIMUM;
      static HUDState NONE;
      static HUDState HELP;
   private:
      HUDState(const std::string &name) : dtUtil::Enumeration(name)
      {
         AddInstance(this);
      }
};

/**
 * This class draws the HUD for the testAAR with using CEGUI.  It draws
 * status information like AAR state (record, playback, idle), sim time,
 * speed factor, num messages, and other help info etc...
 */
class TEST_AAR_EXPORT TestAARHUD : public dtGame::GMComponent
{
   public:

      /**
       * Constructs the test application.
       */
      TestAARHUD(dtCore::DeltaWin &win, 
                 dtCore::Keyboard &keyboard,
                 dtCore::Mouse &mouse,
                 dtGame::LogController &logController, 
                 dtGame::TaskComponent &taskComponent,
                 dtGame::ServerLoggerComponent &serverLogger);
   protected:

      /**
       * Destroys the test application.
       */
      virtual ~TestAARHUD();

   public:

      /**
       * Get messages from the GM component
       */
      virtual void ProcessMessage(const dtGame::Message& message);

      /**
       * Sets up the basic GUI.
       */
      void SetupGUI(dtCore::DeltaWin &win,
                    dtCore::Keyboard &keyboard,
                    dtCore::Mouse &mouse);

      /**
       * Cycles HUD state to the next most data.  From minimal, to moderate, to max,
       * and then back to minimal.
       */
      HUDState &CycleToNextHUDState();

      void SetHUDState(HUDState &newState) { mHUDState = &newState;  UpdateState(); }
      HUDState &GetHUDState() { return *mHUDState; }

      dtGUI::CEUIDrawable* GetGUIDrawable() { return mGUI.get(); }

      void TickHUD();

   protected:

      /**
       * Helper method that creates an actor with random movement behavior.
       */
      //void PlaceActor();

      /**
       * Makes sure to enable/disable controls as appropriate for each state.
       */
      void UpdateState();

      /**
       * Utility method to set the text, position, and color of a text control
       * Check to see if the data changed.  The default values for color and position
       * won't do anything since they use a color and position < 0.
       */
      void UpdateStaticText(CEGUI::Window *textControl, char *newText,
         float red = -1.0f, float green = -1.0f, float blue = -1.0f, float x = -1.0f, float y = -1.0f);

   private:

      /**
       * During the tickHUD() - update our medium data
       */
      void UpdateMediumDetailData();

      /**
       * During the tickHUD() - update our high data
       */
      void UpdateHighDetailData(int baseWidth, float &curYPos);

      /**
       * Add the tasks to the UI.  The tasks have to be worked on as parent/children - so
       * we have to do it recursively.  The numCompleted is increased (+1) if the taskProxy
       * was complete.
       */
      int RecursivelyAddTasks(const std::string &indent, int curIndex,
                              const dtActors::TaskActorProxy *taskProxy, int &numCompleted);

      /**
       * Utility method to create text
       */
      CEGUI::Window *CreateText(const std::string &name, CEGUI::Window *parent, const std::string &text,
                                     float x, float y, float width, float height);

      HUDState *mHUDState;
      HUDState *mLastHUDStateBeforeHelp;

      dtCore::RefPtr<dtGame::LogController> mLogController;
      dtCore::RefPtr<dtGame::TaskComponent> mTaskComponent;
      dtCore::RefPtr<dtGame::ServerLoggerComponent> mServerLoggerComponent;

      dtCore::DeltaWin *mWin;
      CEGUI::Window *mMainWindow;
      dtCore::RefPtr<dtGUI::CEUIDrawable> mGUI;
      CEGUI::Window *mHUDOverlay;
      CEGUI::Window *mHelpOverlay;


      // main info
      CEGUI::Window *mStateText;
      CEGUI::Window *mSimTimeText;
      CEGUI::Window *mSpeedFactorText;
      CEGUI::Window *mNumMessagesText;
      CEGUI::Window *mRecordDurationText;
      CEGUI::Window *mNumTagsText;
      CEGUI::Window *mLastTagText;
      CEGUI::Window *mNumFramesText;
      CEGUI::Window *mLastFrameText;
      CEGUI::Window *mCurLogText;
      CEGUI::Window *mCurMapText;

      // tips messages
      CEGUI::Window *mFirstTipText;
      CEGUI::Window *mSecondTipText;

      // help fields
      CEGUI::Window *mHelpTipText;
      CEGUI::Window *mHelp1Text;
      CEGUI::Window *mHelp2Text;
      CEGUI::Window *mHelp3Text;
      CEGUI::Window *mHelp4Text;
      CEGUI::Window *mHelp5Text;
      CEGUI::Window *mHelp6Text;
      CEGUI::Window *mHelp7Text;
      CEGUI::Window *mHelp8Text;
      CEGUI::Window *mHelp9Text;
      CEGUI::Window *mHelp10Text;
      CEGUI::Window *mHelp11Text;
      CEGUI::Window *mHelp12Text;
      CEGUI::Window *mHelp13Text;
      CEGUI::Window *mHelp14Text;
      CEGUI::Window *mHelp15Text;
      CEGUI::Window *mHelp16Text;
      CEGUI::Window *mHelp17Text;
      CEGUI::Window *mHelp18Text;
      CEGUI::Window *mHelp19Text;

      // task texts
      CEGUI::Window *mTasksHeaderText;
      std::vector<CEGUI::Window *> mTaskTextList;

      float mRightTextXOffset;
      float mTextYTopOffset;
      float mTextYSeparation;
      float mTextHeight;
};

#endif
