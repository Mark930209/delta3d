#include "dt.h"
#include "dtabc.h"
#include "guimgr.h"

using namespace dtABC;
using namespace dtCore;

class TestCloudsApp : public Application
{

public:
   TestCloudsApp( std::string configFilename = "config.xml" )
      : Application( configFilename )
   {
      terr = new InfiniteTerrain();
      terr->SetHorizontalScale(0.01f);
      terr->SetVerticalScale(25.f);
      terr->Regenerate();

      cd = new CloudDome(6, 2, 0.7, 0.5, 0.7, 5, 5500.f, 20);
      cp[0] = new CloudPlane(6, 0.5, 6, 1, .3, 0.96, 256, 1800);
      cp[1] = new CloudPlane(6, 0.7, 12, 1, .4, 0.95, 512, 1000);
      cp[2] = new CloudPlane(6, 0.8, 20, 1, .2, 0.96, 512, 600);

      weather = new Weather();   
      weather->AddDrawable(terr);

      cloudLayers = 1;
      isDomeEnabled = false;
      weather->GetEnvironment()->AddEffect(cp[0].get());
      this->AddDrawable(weather->GetEnvironment());

      Transform xform(0.f, 00.f, 30.f, 0.f, 10.f, 0.f);
      GetCamera()->SetTransform(&xform);

      orbit = new OrbitMotionModel( GetKeyboard(), GetMouse() );
      orbit->SetTarget(GetCamera());
   }



   ~TestCloudsApp()
   {
   }

protected:
   virtual void KeyPressed(dtCore::Keyboard* keyboard, 
      Producer::KeyboardKey key,
      Producer::KeyCharacter character)
   {
      switch(key) {
case Producer::Key_Escape:    this->Quit();    	 break;
case Producer::Key_H:
   {
      GUI *ui = new GUI(); 
   }
   break;
case Producer::Key_F1: weather->SetBasicVisibilityType(Weather::VIS_UNLIMITED); break;
case Producer::Key_F2: weather->SetBasicVisibilityType(Weather::VIS_FAR);       break;
case Producer::Key_F3: weather->SetBasicVisibilityType(Weather::VIS_MODERATE);  break;
case Producer::Key_F4: weather->SetBasicVisibilityType(Weather::VIS_LIMITED);   break;
case Producer::Key_F5: weather->SetBasicVisibilityType(Weather::VIS_CLOSE);     break;
case Producer::Key_P:
   if(isDomeEnabled)
   {
      for(int i = 0; i < cloudLayers; ++i)
         weather->GetEnvironment()->AddEffect(cp[i].get());

      weather->GetEnvironment()->RemEffect(cd.get());
      isDomeEnabled = false;
   }
   break;
case Producer::Key_D:
   if(!isDomeEnabled)
   {
      weather->GetEnvironment()->AddEffect(cd.get());
      isDomeEnabled = true;
      for(int i = 0; i < cloudLayers; ++i)
         weather->GetEnvironment()->RemEffect(cp[i].get());
   }
   break;
case Producer::Key_KP_Add:
case Producer::Key_equal:
   if (!isDomeEnabled && cloudLayers >= 0 && cloudLayers < 3)
   {	
      weather->GetEnvironment()->AddEffect(cp[cloudLayers].get());
      ++cloudLayers;
   }
   break;
case Producer::Key_KP_Subtract:
case Producer::Key_minus:
   if (!isDomeEnabled && cloudLayers > 0)
   {
      --cloudLayers;
      weather->GetEnvironment()->RemEffect(cp[cloudLayers].get());
   }	
   break;
default:
   break;
      }
   }

private:
   InfiniteTerrain *terr;
   Weather *weather;
   OrbitMotionModel *orbit;

   osg::ref_ptr<dtCore::CloudDome>  cd;
   osg::ref_ptr<dtCore::CloudPlane> cp[3];
   int cloudLayers;
   bool isDomeEnabled;

};



int main(int argc, char* argv[])
{
   SetDataFilePathList( "..;" + GetDeltaDataPathList() );
   TestCloudsApp *app = new TestCloudsApp( "config.xml" );
   app->Config();
   app->Run();

   delete app;
   return 0;
}
