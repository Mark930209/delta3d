// generated by Fast Light User Interface Designer (fluid) version 1.0109

#ifndef gui_fltk_h
#define gui_fltk_h
#include <FL/Fl.H>
#include <dtCore/base.h>
#include <dtInspector/export.h>
///Do not create directly - use dtCore::GUI instead
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/Fl_Return_Button.H>

class DT_INSPECTOR_EXPORT UserInterface {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *MainWindow;
  Fl_Browser *InstanceList;
private:
  void cb_InstanceList_i(Fl_Browser*, void*);
  static void cb_InstanceList(Fl_Browser*, void*);
  Fl_Box *InstanceClassName;
public:
  Fl_Group *BaseGroup;
private:
  Fl_Input *BaseName;
  void cb_BaseName_i(Fl_Input*, void*);
  static void cb_BaseName(Fl_Input*, void*);
public:
  Fl_Value_Output *BaseReferenceCount;
  Fl_Group *DrawableGroup;
private:
  Fl_Browser *DrawableChildList;
  void cb__i(Fl_Button*, void*);
  static void cb_(Fl_Button*, void*);
  void cb_1_i(Fl_Button*, void*);
  static void cb_1(Fl_Button*, void*);
  Fl_Output *DrawableParentText;
public:
  Fl_Group *TransformGroup;
private:
  Fl_Value_Input *TransformX;
  void cb_TransformX_i(Fl_Value_Input*, void*);
  static void cb_TransformX(Fl_Value_Input*, void*);
  Fl_Value_Input *TransformY;
  void cb_TransformY_i(Fl_Value_Input*, void*);
  static void cb_TransformY(Fl_Value_Input*, void*);
  Fl_Value_Input *TransformZ;
  void cb_TransformZ_i(Fl_Value_Input*, void*);
  static void cb_TransformZ(Fl_Value_Input*, void*);
  Fl_Value_Input *TransformH;
  void cb_TransformH_i(Fl_Value_Input*, void*);
  static void cb_TransformH(Fl_Value_Input*, void*);
  Fl_Value_Input *TransformP;
  void cb_TransformP_i(Fl_Value_Input*, void*);
  static void cb_TransformP(Fl_Value_Input*, void*);
  Fl_Value_Input *TransformR;
  void cb_TransformR_i(Fl_Value_Input*, void*);
  static void cb_TransformR(Fl_Value_Input*, void*);
  Fl_Round_Button *TransformCSAbsButton;
  void cb_TransformCSAbsButton_i(Fl_Round_Button*, void*);
  static void cb_TransformCSAbsButton(Fl_Round_Button*, void*);
  Fl_Round_Button *TransformCSRelButton;
  void cb_TransformCSRelButton_i(Fl_Round_Button*, void*);
  static void cb_TransformCSRelButton(Fl_Round_Button*, void*);
public:
  Fl_Group *LoadableGroup;
private:
  Fl_Input *LoadableFilename;
  void cb_LoadableFilename_i(Fl_Input*, void*);
  static void cb_LoadableFilename(Fl_Input*, void*);
  void cb_2_i(Fl_Button*, void*);
  static void cb_2(Fl_Button*, void*);
public:
  Fl_Group *CameraGroup;
private:
  Fl_Value_Input *CameraClearRed;
  void cb_CameraClearRed_i(Fl_Value_Input*, void*);
  static void cb_CameraClearRed(Fl_Value_Input*, void*);
  Fl_Value_Input *CameraClearGreen;
  void cb_CameraClearGreen_i(Fl_Value_Input*, void*);
  static void cb_CameraClearGreen(Fl_Value_Input*, void*);
  Fl_Value_Input *CameraClearBlue;
  void cb_CameraClearBlue_i(Fl_Value_Input*, void*);
  static void cb_CameraClearBlue(Fl_Value_Input*, void*);
  Fl_Button *CameraClearLoadButton;
  void cb_CameraClearLoadButton_i(Fl_Button*, void*);
  static void cb_CameraClearLoadButton(Fl_Button*, void*);
  Fl_Choice *CameraWinChoice;
  void cb_CameraWinChoice_i(Fl_Choice*, void*);
  static void cb_CameraWinChoice(Fl_Choice*, void*);
  void cb_Next_i(Fl_Button*, void*);
  static void cb_Next(Fl_Button*, void*);
public:
  Fl_Group *WindowGroup;
private:
  Fl_Value_Input *WinPosW;
  void cb_WinPosW_i(Fl_Value_Input*, void*);
  static void cb_WinPosW(Fl_Value_Input*, void*);
  Fl_Value_Input *WinPosH;
  void cb_WinPosH_i(Fl_Value_Input*, void*);
  static void cb_WinPosH(Fl_Value_Input*, void*);
  Fl_Menu_Button *WinSizeButton;
  void cb_WinSizeButton_i(Fl_Menu_Button*, void*);
  static void cb_WinSizeButton(Fl_Menu_Button*, void*);
  static Fl_Menu_Item menu_WinSizeButton[];
  Fl_Value_Input *WinPosX;
  void cb_WinPosX_i(Fl_Value_Input*, void*);
  static void cb_WinPosX(Fl_Value_Input*, void*);
  Fl_Value_Input *WinPosY;
  void cb_WinPosY_i(Fl_Value_Input*, void*);
  static void cb_WinPosY(Fl_Value_Input*, void*);
  Fl_Check_Button *WinCursorToggle;
  void cb_WinCursorToggle_i(Fl_Check_Button*, void*);
  static void cb_WinCursorToggle(Fl_Check_Button*, void*);
  Fl_Input *WinTitle;
  void cb_WinTitle_i(Fl_Input*, void*);
  static void cb_WinTitle(Fl_Input*, void*);
  Fl_Check_Button *WinFullScreenToggle;
  void cb_WinFullScreenToggle_i(Fl_Check_Button*, void*);
  static void cb_WinFullScreenToggle(Fl_Check_Button*, void*);
public:
  Fl_Group *ViewGroup;
  Fl_Choice *ViewSceneChoice;
private:
  void cb_ViewSceneChoice_i(Fl_Choice*, void*);
  static void cb_ViewSceneChoice(Fl_Choice*, void*);
public:
  Fl_Choice *ViewCameraChoice;
private:
  void cb_ViewCameraChoice_i(Fl_Choice*, void*);
  static void cb_ViewCameraChoice(Fl_Choice*, void*);
public:
  Fl_Group *SkyBoxGroup;
private:
  Fl_Value_Input *SkyBoxBaseRed;
  void cb_SkyBoxBaseRed_i(Fl_Value_Input*, void*);
  static void cb_SkyBoxBaseRed(Fl_Value_Input*, void*);
  Fl_Value_Input *SkyBoxBaseGreen;
  void cb_SkyBoxBaseGreen_i(Fl_Value_Input*, void*);
  static void cb_SkyBoxBaseGreen(Fl_Value_Input*, void*);
  Fl_Value_Input *SkyBoxBaseBlue;
  void cb_SkyBoxBaseBlue_i(Fl_Value_Input*, void*);
  static void cb_SkyBoxBaseBlue(Fl_Value_Input*, void*);
  Fl_Button *SkyBoxBaseColorLoadButton;
  void cb_SkyBoxBaseColorLoadButton_i(Fl_Button*, void*);
  static void cb_SkyBoxBaseColorLoadButton(Fl_Button*, void*);
public:
  Fl_Group *EnvironmentGroup;
  Fl_Group *EnvFogColorGroup;
private:
  Fl_Value_Input *FogRed;
  void cb_FogRed_i(Fl_Value_Input*, void*);
  static void cb_FogRed(Fl_Value_Input*, void*);
  Fl_Value_Input *FogGreen;
  void cb_FogGreen_i(Fl_Value_Input*, void*);
  static void cb_FogGreen(Fl_Value_Input*, void*);
  Fl_Value_Input *FogBlue;
  void cb_FogBlue_i(Fl_Value_Input*, void*);
  static void cb_FogBlue(Fl_Value_Input*, void*);
  Fl_Button *FogColorLoadButton;
  void cb_FogColorLoadButton_i(Fl_Button*, void*);
  static void cb_FogColorLoadButton(Fl_Button*, void*);
public:
  Fl_Group *EnvAdvFogGroup;
private:
  Fl_Value_Input *AdvFogTurbidity;
  void cb_AdvFogTurbidity_i(Fl_Value_Input*, void*);
  static void cb_AdvFogTurbidity(Fl_Value_Input*, void*);
  Fl_Value_Input *AdvFogEnergy;
  void cb_AdvFogEnergy_i(Fl_Value_Input*, void*);
  static void cb_AdvFogEnergy(Fl_Value_Input*, void*);
  Fl_Value_Input *AdvFogMolecules;
  void cb_AdvFogMolecules_i(Fl_Value_Input*, void*);
  static void cb_AdvFogMolecules(Fl_Value_Input*, void*);
  Fl_Value_Input *EnvFogVis;
  void cb_EnvFogVis_i(Fl_Value_Input*, void*);
  static void cb_EnvFogVis(Fl_Value_Input*, void*);
  Fl_Value_Input *EnvFogNear;
  void cb_EnvFogNear_i(Fl_Value_Input*, void*);
  static void cb_EnvFogNear(Fl_Value_Input*, void*);
public:
  Fl_Choice *EnvFogMode;
private:
  void cb_EnvFogMode_i(Fl_Choice*, void*);
  static void cb_EnvFogMode(Fl_Choice*, void*);
  static Fl_Menu_Item menu_EnvFogMode[];
  Fl_Check_Button *EnvFogEnable;
  void cb_EnvFogEnable_i(Fl_Check_Button*, void*);
  static void cb_EnvFogEnable(Fl_Check_Button*, void*);
  Fl_Value_Input *SkyRed;
  void cb_SkyRed_i(Fl_Value_Input*, void*);
  static void cb_SkyRed(Fl_Value_Input*, void*);
  Fl_Value_Input *SkyGreen;
  void cb_SkyGreen_i(Fl_Value_Input*, void*);
  static void cb_SkyGreen(Fl_Value_Input*, void*);
  Fl_Value_Input *SkyBlue;
  void cb_SkyBlue_i(Fl_Value_Input*, void*);
  static void cb_SkyBlue(Fl_Value_Input*, void*);
  Fl_Button *SkyColorLoadButton;
  void cb_SkyColorLoadButton_i(Fl_Button*, void*);
  static void cb_SkyColorLoadButton(Fl_Button*, void*);
  Fl_Value_Input *EnvSunRed;
  Fl_Value_Input *EnvSunGreen;
  Fl_Value_Input *EnvSunBlue;
  Fl_Value_Input *EnvRefLat;
  void cb_EnvRefLat_i(Fl_Value_Input*, void*);
  static void cb_EnvRefLat(Fl_Value_Input*, void*);
  Fl_Value_Input *EnvRefLong;
  void cb_EnvRefLong_i(Fl_Value_Input*, void*);
  static void cb_EnvRefLong(Fl_Value_Input*, void*);
public:
  Fl_Value_Slider *EnvTimeOfDay;
private:
  void cb_EnvTimeOfDay_i(Fl_Value_Slider*, void*);
  static void cb_EnvTimeOfDay(Fl_Value_Slider*, void*);
public:
  Fl_Value_Input *EnvYear;
private:
  void cb_EnvYear_i(Fl_Value_Input*, void*);
  static void cb_EnvYear(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *EnvMonth;
private:
  void cb_EnvMonth_i(Fl_Value_Input*, void*);
  static void cb_EnvMonth(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *EnvDay;
private:
  void cb_EnvDay_i(Fl_Value_Input*, void*);
  static void cb_EnvDay(Fl_Value_Input*, void*);
public:
  Fl_Group *InfTerrainGroup;
  Fl_Value_Input *InfBuildDistance;
  Fl_Value_Input *InfSegSize;
  Fl_Value_Input *InfSegDivisions;
  Fl_Value_Input *InfVertScale;
  Fl_Value_Input *InfHorizScale;
  Fl_Button *InfRegenerateButton;
private:
  void cb_InfRegenerateButton_i(Fl_Button*, void*);
  static void cb_InfRegenerateButton(Fl_Button*, void*);
public:
  Fl_Check_Button *InfSmoothCollision;
private:
  void cb_InfSmoothCollision_i(Fl_Check_Button*, void*);
  static void cb_InfSmoothCollision(Fl_Check_Button*, void*);
public:
  Fl_Group *CloudEditor;
  Fl_Value_Slider *cScale;
private:
  void cb_cScale_i(Fl_Value_Slider*, void*);
  static void cb_cScale(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *cCutoff;
private:
  void cb_cCutoff_i(Fl_Value_Slider*, void*);
  static void cb_cCutoff(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *cExponent;
private:
  void cb_cExponent_i(Fl_Value_Slider*, void*);
  static void cb_cExponent(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *cBias;
private:
  void cb_cBias_i(Fl_Value_Slider*, void*);
  static void cb_cBias(Fl_Value_Slider*, void*);
public:
  Fl_Value_Input *CloudRed;
private:
  void cb_CloudRed_i(Fl_Value_Input*, void*);
  static void cb_CloudRed(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *CloudGreen;
private:
  void cb_CloudGreen_i(Fl_Value_Input*, void*);
  static void cb_CloudGreen(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *CloudBlue;
private:
  void cb_CloudBlue_i(Fl_Value_Input*, void*);
  static void cb_CloudBlue(Fl_Value_Input*, void*);
  Fl_Button *CloudColorLoadButton;
  void cb_CloudColorLoadButton_i(Fl_Button*, void*);
  static void cb_CloudColorLoadButton(Fl_Button*, void*);
public:
  Fl_Value_Slider *cSpeedX;
private:
  void cb_cSpeedX_i(Fl_Value_Slider*, void*);
  static void cb_cSpeedX(Fl_Value_Slider*, void*);
public:
  Fl_Value_Slider *cSpeedY;
private:
  void cb_cSpeedY_i(Fl_Value_Slider*, void*);
  static void cb_cSpeedY(Fl_Value_Slider*, void*);
public:
  Fl_Check_Button *cEnable;
private:
  void cb_cEnable_i(Fl_Check_Button*, void*);
  static void cb_cEnable(Fl_Check_Button*, void*);
public:
  Fl_Group *WeatherGroup;
  Fl_Choice *WeatherTimePeriodChoice;
private:
  void cb_WeatherTimePeriodChoice_i(Fl_Choice*, void*);
  static void cb_WeatherTimePeriodChoice(Fl_Choice*, void*);
  static Fl_Menu_Item menu_WeatherTimePeriodChoice[];
public:
  Fl_Choice *WeatherSeasonChoice;
private:
  void cb_WeatherSeasonChoice_i(Fl_Choice*, void*);
  static void cb_WeatherSeasonChoice(Fl_Choice*, void*);
  static Fl_Menu_Item menu_WeatherSeasonChoice[];
public:
  Fl_Group *WeatherCustomGroup;
  Fl_Slider *WeatherCloudSlider;
private:
  void cb_WeatherCloudSlider_i(Fl_Slider*, void*);
  static void cb_WeatherCloudSlider(Fl_Slider*, void*);
public:
  Fl_Slider *WeatherWindSlider;
private:
  void cb_WeatherWindSlider_i(Fl_Slider*, void*);
  static void cb_WeatherWindSlider(Fl_Slider*, void*);
public:
  Fl_Slider *WeatherVisSlider;
private:
  void cb_WeatherVisSlider_i(Fl_Slider*, void*);
  static void cb_WeatherVisSlider(Fl_Slider*, void*);
public:
  Fl_Round_Button *WeatherThemeOption;
private:
  void cb_WeatherThemeOption_i(Fl_Round_Button*, void*);
  static void cb_WeatherThemeOption(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *WeatherCustomOption;
private:
  void cb_WeatherCustomOption_i(Fl_Round_Button*, void*);
  static void cb_WeatherCustomOption(Fl_Round_Button*, void*);
public:
  Fl_Group *WeatherThemeGroup;
  Fl_Round_Button *WeatherThemeClearOption;
private:
  void cb_WeatherThemeClearOption_i(Fl_Round_Button*, void*);
  static void cb_WeatherThemeClearOption(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *WeatherThemeFairOption;
private:
  void cb_WeatherThemeFairOption_i(Fl_Round_Button*, void*);
  static void cb_WeatherThemeFairOption(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *WeatherThemeFoggyOption;
private:
  void cb_WeatherThemeFoggyOption_i(Fl_Round_Button*, void*);
  static void cb_WeatherThemeFoggyOption(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *WeatherThemeRainyOption;
private:
  void cb_WeatherThemeRainyOption_i(Fl_Round_Button*, void*);
  static void cb_WeatherThemeRainyOption(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *WeatherThemeCustomOption;
private:
  void cb_WeatherThemeCustomOption_i(Fl_Round_Button*, void*);
  static void cb_WeatherThemeCustomOption(Fl_Round_Button*, void*);
public:
  Fl_Value_Slider *WeatherRateOfChangeSlider;
private:
  void cb_WeatherRateOfChangeSlider_i(Fl_Value_Slider*, void*);
  static void cb_WeatherRateOfChangeSlider(Fl_Value_Slider*, void*);
public:
  Fl_Group *LightGroup;
private:
  Fl_Value_Input *LightNumberInput;
  void cb_LightNumberInput_i(Fl_Value_Input*, void*);
  static void cb_LightNumberInput(Fl_Value_Input*, void*);
public:
  Fl_Round_Button *LightModeLocal;
private:
  void cb_LightModeLocal_i(Fl_Round_Button*, void*);
  static void cb_LightModeLocal(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *LightModeGlobal;
private:
  void cb_LightModeGlobal_i(Fl_Round_Button*, void*);
  static void cb_LightModeGlobal(Fl_Round_Button*, void*);
  Fl_Value_Input *LightDifRed;
  void cb_LightDifRed_i(Fl_Value_Input*, void*);
  static void cb_LightDifRed(Fl_Value_Input*, void*);
  Fl_Value_Input *LightDifGreen;
  void cb_LightDifGreen_i(Fl_Value_Input*, void*);
  static void cb_LightDifGreen(Fl_Value_Input*, void*);
  Fl_Value_Input *LightDifBlue;
  void cb_LightDifBlue_i(Fl_Value_Input*, void*);
  static void cb_LightDifBlue(Fl_Value_Input*, void*);
  Fl_Button *LightDifColorLoadButton;
  void cb_LightDifColorLoadButton_i(Fl_Button*, void*);
  static void cb_LightDifColorLoadButton(Fl_Button*, void*);
  Fl_Value_Input *LightAmbRed;
  void cb_LightAmbRed_i(Fl_Value_Input*, void*);
  static void cb_LightAmbRed(Fl_Value_Input*, void*);
  Fl_Value_Input *LightAmbGreen;
  void cb_LightAmbGreen_i(Fl_Value_Input*, void*);
  static void cb_LightAmbGreen(Fl_Value_Input*, void*);
  Fl_Value_Input *LightAmbBlue;
  void cb_LightAmbBlue_i(Fl_Value_Input*, void*);
  static void cb_LightAmbBlue(Fl_Value_Input*, void*);
  Fl_Button *LightAmbColorLoadButton;
  void cb_LightAmbColorLoadButton_i(Fl_Button*, void*);
  static void cb_LightAmbColorLoadButton(Fl_Button*, void*);
  Fl_Value_Input *LightSpecRed;
  void cb_LightSpecRed_i(Fl_Value_Input*, void*);
  static void cb_LightSpecRed(Fl_Value_Input*, void*);
  Fl_Value_Input *LightSpecGreen;
  void cb_LightSpecGreen_i(Fl_Value_Input*, void*);
  static void cb_LightSpecGreen(Fl_Value_Input*, void*);
  Fl_Value_Input *LightSpecBlue;
  void cb_LightSpecBlue_i(Fl_Value_Input*, void*);
  static void cb_LightSpecBlue(Fl_Value_Input*, void*);
  Fl_Button *LightSpecColorLoadButton;
  void cb_LightSpecColorLoadButton_i(Fl_Button*, void*);
  static void cb_LightSpecColorLoadButton(Fl_Button*, void*);
public:
  Fl_Group *PositionalLightGroup;
private:
  Fl_Value_Input *LightConstAtt;
  void cb_LightConstAtt_i(Fl_Value_Input*, void*);
  static void cb_LightConstAtt(Fl_Value_Input*, void*);
  Fl_Value_Input *LightLinAtt;
  void cb_LightLinAtt_i(Fl_Value_Input*, void*);
  static void cb_LightLinAtt(Fl_Value_Input*, void*);
  Fl_Value_Input *LightQuadAtt;
  void cb_LightQuadAtt_i(Fl_Value_Input*, void*);
  static void cb_LightQuadAtt(Fl_Value_Input*, void*);
public:
  Fl_Group *LightSpotGroup;
private:
  Fl_Value_Input *LightExponentInput;
  void cb_LightExponentInput_i(Fl_Value_Input*, void*);
  static void cb_LightExponentInput(Fl_Value_Input*, void*);
  Fl_Value_Input *LightCutoffInput;
  void cb_LightCutoffInput_i(Fl_Value_Input*, void*);
  static void cb_LightCutoffInput(Fl_Value_Input*, void*);
public:
  Fl_Group *InfiniteLightGroup;
private:
  Fl_Value_Input *InfLightAzInput;
  void cb_InfLightAzInput_i(Fl_Value_Input*, void*);
  static void cb_InfLightAzInput(Fl_Value_Input*, void*);
  Fl_Value_Input *InfLightElevInput;
  void cb_InfLightElevInput_i(Fl_Value_Input*, void*);
  static void cb_InfLightElevInput(Fl_Value_Input*, void*);
public:
  Fl_Group *ParticleGroup;
  Fl_Check_Button *ParticleEnabled;
private:
  void cb_ParticleEnabled_i(Fl_Check_Button*, void*);
  static void cb_ParticleEnabled(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *ParticleParentRelative;
private:
  void cb_ParticleParentRelative_i(Fl_Check_Button*, void*);
  static void cb_ParticleParentRelative(Fl_Check_Button*, void*);
public:
  Fl_Double_Window *SelectWindow;
private:
  Fl_Check_Browser *SelectList;
  Fl_Return_Button *SelectWinAddButton;
public:
  Fl_Button *SelectWinCancelButton;
  void SelectInstance(void); 
private:
  static dtCore::Base *GetSelectedInstance( UserInterface *ui); 
  void BaseNameCB(Fl_Input *o); 
  void DrawableAddChildCB( Fl_Button *); 
  void DrawableRemChildCB( Fl_Button *); 
  void TransformPosCB( Fl_Value_Input *); 
  void TransformCSCB( Fl_Round_Button *); 
  void CameraClearColorBrowserCB(Fl_Button*); 
  void CameraClearColorCB(Fl_Value_Input* ); 
  void CameraWinCB(Fl_Choice *); 
  void WinPosCB( Fl_Value_Input * ); 
  void WinSizeCB( Fl_Menu_Button * ); 
  void WinCursorCB( Fl_Check_Button * ); 
  void WinFullScreenCB( Fl_Check_Button * ); 
  void WinTitleCB( Fl_Input * ); 
  void LoadableFileCB( Fl_Input * ); 
  void LoadableLoadFileCB( Fl_Button * ); 
  void SkyBoxBaseColorCB(Fl_Value_Input *); 
  void SkyBoxBaseColorBrowserCB(Fl_Button*); 
  void EnvFogColorCB(Fl_Value_Input *); 
  void EnvAdvFogCB(Fl_Value_Input *); 
  void EnvFogColorBrowserCB(Fl_Button*); 
  void EnvFogVisCB(Fl_Value_Input*); 
  void EnvFogNearCB(Fl_Value_Input*); 
  void EnvFogEnableCB(Fl_Check_Button*); 
  void EnvFogModeCB(Fl_Choice*); 
  void EnvSkyColorCB(Fl_Value_Input*); 
  void EnvSkyColorBrowserCB(Fl_Button*); 
  void EnvDateTimeCB(Fl_Value_Input*); 
  void EnvTimeCB(Fl_Value_Slider*); 
  void EnvRefPosCB(Fl_Value_Input *); 
  void InfRegenerateCB(Fl_Button*); 
  void InfSmoothCDCB(Fl_Check_Button*); 
  void CloudColorCB(Fl_Value_Input *); 
  void CloudColorBrowserCB(Fl_Button*); 
  void CloudScaleCB(Fl_Value_Slider*); 
  void CloudCutoffCB(Fl_Value_Slider*); 
  void CloudExponentCB(Fl_Value_Slider*); 
  void CloudWindCB(Fl_Value_Slider*); 
  void CloudEnableCB(Fl_Check_Button*); 
  void CloudBiasCB(Fl_Value_Slider*); 
  void WeatherThemeCustomOptionCB(Fl_Round_Button*); 
  void WeatherThemeCB(Fl_Round_Button*); 
  void WeatherCustomCloudCB(Fl_Slider*); 
  void WeatherCustomWindCB(Fl_Slider*); 
  void WeatherCustomVisCB(Fl_Slider*); 
  void WeatherTimeCB(Fl_Choice*); 
  void WeatherSeasonCB(Fl_Choice*); 
  void WeatherRateOfChangeCB(Fl_Value_Slider*); 
  void LightModeCB(Fl_Round_Button*); 
  void LightNumCB(Fl_Value_Input*); 
  void LightAmbColorCB(Fl_Value_Input*); 
  void LightDifColorCB(Fl_Value_Input*); 
  void LightSpecColorCB(Fl_Value_Input*); 
  void LightAmbColorBrowserCB(Fl_Button*); 
  void LightDifColorBrowserCB(Fl_Button*); 
  void LightSpecColorBrowserCB(Fl_Button*); 
  void LightAttCB(Fl_Value_Input*); 
  void LightSpotCB(Fl_Value_Input*); 
  void InfLightCB(Fl_Value_Input*); 
  void ParticleRelativeCB(Fl_Check_Button*); 
  void ParticleEnabledCB(Fl_Check_Button*); 
  void CamStatisticsCB(Fl_Button*); 
  void ViewSceneCB(Fl_Choice*); 
  void ViewCameraCB(Fl_Choice*); 
};
#endif
