#pragma once
#include <vector>
typedef unsigned char byte;
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp" 
using namespace cv;
using namespace std;
enum StatusCode
{
	DCM_INIT_OK = 10,//初始化成功
/*******初始化失败的状态都需要关闭程序，重新开启程序！********/
	DCM_ELC_INIT_ERROR,//电机初始化失败！
	DCM_XML_INIT_ERROR,//配置文件读取失败！
	DCM_GETPICCAMERA_INIT_ERROR,//采集相机初始化失败！
	DCM_USB_INIT_ERROR,//单片机初始化失败！
	DCM_LOCATECAMERA_INIT_ERROR,//定位相机初始化失败！
	DCM_ELCORG_INIT_ERROR,//电机归零失败！
/*******初始化失败的状态都需要关闭程序，重新开启程序！********/
    DCM_GETSLIDEPREVIEW_OK,//定位命令成功
    DCM_GETSLIDEPREVIEW_ERROR,//定位命令失败
	DCM_TENSCANMOVING_START,//正在进行十倍镜扫描
	DCM_TENSCANMOVING_FINISH,//十倍镜扫描结束
	DCM_TENSCANMOVING_ERROR,//十倍镜扫描异常
	DCM_HUNDREDSCANMOVING_START,//正在进行百倍镜扫描
	DCM_HUNDREDSCANMOVING_FINISH,//百倍镜扫描结束
	DCM_HUNDREDSCANMOVING_ERROR,//百倍镜扫描异常
	DCM_STATUSGOOD,//机器状态良好
	DCM_TERRIBLEERROR,//严重性错误，需要重启硬件和程序
};
//百倍扫描模式
enum HundredScanType
{
	DCM_HUNDREDSCANMOVING_TYPE_BLOOD=100,//外周血扫描
	DCM_HUNDREDSCANMOVING_TYPE_BONE,//骨髓扫描
};
//图片格式
enum PictureType
{
	DCM_PICTURETYPE_COLOR = 200,//彩色
	DCM_PICTURETYPE_GRAY,//黑白
};
//扫描信息结构体
struct ScanInfo
{
	int x;
	int y;
	int width;
	int height;
	int column;
	int row;
};
//传出图片结构体
struct PicInfor
{
	byte* matPic;
	pair<int, int> point;
	int width;
	int height;
	PictureType pictureType;
};
//电机运动的速度
enum MachineMoveSpeed
{
	HEIGHTSPEED = 0,//最高速
	MIDDLESPEED,//中速
	LOWSPEED,//低速
};
struct InInFor//输入信息，接收深析那边传入的信息，比如设置产品规格等
{
String inFor[200];//暂定两百条信息，不够以后再扩
};
struct OutInFor//输出信息，从生强API获取输出信息，比如硬件固件号，API版本等等
{
String outFor[200];//暂定两百条信息，不够以后再扩
//0，API版本
//1，机器ID号
//2，单片机固件版本
//3，出厂日期
};
//电机运动的方向
enum MachineMoveDir
{
	XPlus = 0,//X正方向
	XMinus,//X负方向
	YPlus,//Y正方向
	YMinus,//Y负方向
	ZPlus,//Z正方向
	ZMinus,//Z负方向
};
//物镜选择
enum Mirror
{
	TEN = 0,//十倍镜
	HUNDRED,//百倍镜
};
extern "C" _declspec(dllexport)  StatusCode Initialize();
extern "C" _declspec(dllexport)  StatusCode GetSlidePreview(vector<PicInfor>* picList, ScanInfo* scanInfo, string* QRcode);
extern "C" _declspec(dllexport)  StatusCode TenScanMoving(ScanInfo* scanInfo);
extern "C" _declspec(dllexport)  void GetRealTimePics(vector<PicInfor>* outputPicList);
extern "C" _declspec(dllexport)  StatusCode HundredScanMoving(vector<pair<pair<int, int>, pair<int, int>>> points, ScanInfo* scanInfo, HundredScanType hundredScanType,bool ifOil,bool scanFinishReturn);
extern "C" _declspec(dllexport)  StatusCode NormalStatusCheck();
extern "C" _declspec(dllexport)  StatusCode ExtremeStatusCheck();
extern "C" _declspec(dllexport)  void StopCommand();
extern "C" _declspec(dllexport)  void CloseMachine();
extern "C" _declspec(dllexport)  void MachineMoveStart(MachineMoveSpeed speed, MachineMoveDir dir);//XY轴推荐MIDDLESPEED中速，Z轴推荐LOWSPEED低速
extern "C" _declspec(dllexport)  void MachineMoveStop(MachineMoveDir dir);//调用MachineMoveStart(MachineMoveSpeed speed, MachineMoveDir dir)一次就会一直运动，只有调用了MachineMoveStop(MachineMoveDir dir)才会停止
extern "C" _declspec(dllexport)  void LedControl(int lightValue, Mirror mirror);//lightValue范围在0-100,0相当于关灯，100相当于满电压
extern "C" _declspec(dllexport)  void ReturnXYZSPoint(int value[4]);//返回四个轴的坐标（脉冲）
extern "C" _declspec(dllexport)  void ChangeMirror(Mirror mirror);//切换物镜
extern "C" _declspec(dllexport)  void MoveToOil();//载物台移动到油管正下方
extern "C" _declspec(dllexport)  void AddOil();//滴下适量的油
extern "C" _declspec(dllexport)  void MoveToSetXY(int X, int Y);//移动到指定的XY坐标（脉冲值）
extern "C" _declspec(dllexport)  void SetInFor(InInFor inInFor);//接收深析传来的信息,初始化之前调用
extern "C" _declspec(dllexport)  OutInFor GetInFor();//接收生强传来的信息,初始化成功后才能调用
extern "C" _declspec(dllexport)  double MoveStepToGetResolPower(Mirror mirror);//物镜X正向移动一个倍数图片视野，返回像素分辨率
extern "C" _declspec(dllexport)  void OpenManualMode();//打开实时图像
extern "C" _declspec(dllexport)  void CloseManualMode();//关闭实时图像
extern "C" _declspec(dllexport)  void ReturnToGetSlide();//定位识别不出区域时，调此函数，到退片位置
extern "C" _declspec(dllexport)  void ClearManualPics(int clearCount);//清除实时图像队列
extern "C" _declspec(dllexport)  void ReturnScanRoi(pair<int, int> scanroi[4]);//获取扫描区域