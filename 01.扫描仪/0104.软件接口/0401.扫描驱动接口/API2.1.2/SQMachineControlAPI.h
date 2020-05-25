#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp" 
using namespace cv;
using namespace std;
enum StatusCode
{
	DCM_INIT_OK = 10,//��ʼ���ɹ�
/*******��ʼ��ʧ�ܵ�״̬����Ҫ�رճ������¿�������********/
	DCM_ELC_INIT_ERROR,//�����ʼ��ʧ�ܣ�
	DCM_XML_INIT_ERROR,//�����ļ���ȡʧ�ܣ�
	DCM_GETPICCAMERA_INIT_ERROR,//�ɼ������ʼ��ʧ�ܣ�
	DCM_USB_INIT_ERROR,//��Ƭ����ʼ��ʧ�ܣ�
	DCM_LOCATECAMERA_INIT_ERROR,//��λ�����ʼ��ʧ�ܣ�
	DCM_ELCORG_INIT_ERROR,//�������ʧ�ܣ�
/*******��ʼ��ʧ�ܵ�״̬����Ҫ�رճ������¿�������********/
    DCM_GETSLIDEPREVIEW_OK,//��λ����ɹ�
    DCM_GETSLIDEPREVIEW_ERROR,//��λ����ʧ��
	DCM_TENSCANMOVING_START,//���ڽ���ʮ����ɨ��
	DCM_TENSCANMOVING_FINISH,//ʮ����ɨ�����
	DCM_TENSCANMOVING_ERROR,//ʮ����ɨ���쳣
	DCM_HUNDREDSCANMOVING_START,//���ڽ��аٱ���ɨ��
	DCM_HUNDREDSCANMOVING_FINISH,//�ٱ���ɨ�����
	DCM_HUNDREDSCANMOVING_ERROR,//�ٱ���ɨ���쳣
	DCM_STATUSGOOD,//����״̬����
	DCM_TERRIBLEERROR,//�����Դ�����Ҫ����Ӳ���ͳ���
};
//�ٱ�ɨ��ģʽ
enum HundredScanType
{
	DCM_HUNDREDSCANMOVING_TYPE_BLOOD=100,//����Ѫɨ��
	DCM_HUNDREDSCANMOVING_TYPE_BONE,//����ɨ��
};
//ͼƬ��ʽ
enum PictureType
{
	DCM_PICTURETYPE_COLOR = 200,//��ɫ
	DCM_PICTURETYPE_GRAY,//�ڰ�
};
//ɨ����Ϣ�ṹ��
struct ScanInfo
{
	int x;
	int y;
	int width;
	int height;
	int column;
	int row;
};
//����ͼƬ�ṹ��
struct PicInfor
{
	byte* matPic;
	pair<int, int> point;
	int width;
	int height;
	PictureType pictureType;
};
//����˶����ٶ�
enum MachineMoveSpeed
{
	HEIGHTSPEED = 0,//�����
	MIDDLESPEED,//����
	LOWSPEED,//����
};
struct InInFor//������Ϣ�����������Ǳߴ������Ϣ���������ò�Ʒ����
{
String inFor[200];//�ݶ���������Ϣ�������Ժ�����
};
struct OutInFor//�����Ϣ������ǿAPI��ȡ�����Ϣ������Ӳ���̼��ţ�API�汾�ȵ�
{
String outFor[200];//�ݶ���������Ϣ�������Ժ�����
//0��API�汾
//1������ID��
//2����Ƭ���̼��汾
//3����������
};
//����˶��ķ���
enum MachineMoveDir
{
	XPlus = 0,//X������
	XMinus,//X������
	YPlus,//Y������
	YMinus,//Y������
	ZPlus,//Z������
	ZMinus,//Z������
};
//�ﾵѡ��
enum Mirror
{
	TEN = 0,//ʮ����
	HUNDRED,//�ٱ���
};
//����ɨ��ģʽ
enum BoneScanModel
{
	ALONE=0,//����ģʽ��ʮ��ɨ��󣬵��ô�ģʽ
	CONTINUITY,//����ģʽ������Ѫɨ��󣬵��ô�ģʽ
};
extern "C" _declspec(dllexport)  StatusCode Initialize();
extern "C" _declspec(dllexport)  StatusCode GetSlidePreview(vector<PicInfor>* picList, ScanInfo* scanInfo, string* QRcode);
extern "C" _declspec(dllexport)  StatusCode TenScanMoving(ScanInfo* scanInfo);
extern "C" _declspec(dllexport)  void GetRealTimePics(vector<PicInfor>* outputPicList);
extern "C" _declspec(dllexport)  StatusCode HundredScanMoving(vector<pair<pair<int, int>, pair<int, int>>> points, ScanInfo* scanInfo, HundredScanType hundredScanType,bool ifOil,BoneScanModel boneScanModel);//ʹ��CONTINUITYģʽʱ������Ѫ�͹��趼�������ģʽ
extern "C" _declspec(dllexport)  StatusCode NormalStatusCheck();
extern "C" _declspec(dllexport)  StatusCode ExtremeStatusCheck();
extern "C" _declspec(dllexport)  void StopCommand();
extern "C" _declspec(dllexport)  void CloseMachine();
extern "C" _declspec(dllexport)  void MachineMoveStart(MachineMoveSpeed speed, MachineMoveDir dir);//XY���Ƽ�MIDDLESPEED���٣�Z���Ƽ�LOWSPEED����
extern "C" _declspec(dllexport)  void MachineMoveStop(MachineMoveDir dir);//����MachineMoveStart(MachineMoveSpeed speed, MachineMoveDir dir)һ�ξͻ�һֱ�˶���ֻ�е�����MachineMoveStop(MachineMoveDir dir)�Ż�ֹͣ
extern "C" _declspec(dllexport)  void LedControl(int lightValue, Mirror mirror);//lightValue��Χ��0-100,0�൱�ڹصƣ�100�൱������ѹ
extern "C" _declspec(dllexport)  void ReturnXYZSPoint(int value[4]);//�����ĸ�������꣨���壩
extern "C" _declspec(dllexport)  void ChangeMirror(Mirror mirror);//�л��ﾵ
extern "C" _declspec(dllexport)  void MoveToOil();//����̨�ƶ����͹����·�
extern "C" _declspec(dllexport)  void AddOil();//������������
extern "C" _declspec(dllexport)  void MoveToSetXY(int X, int Y);//�ƶ���ָ����XY���꣨����ֵ��
extern "C" _declspec(dllexport)  void SetInFor(InInFor inInFor);//����������������Ϣ,��ʼ��֮ǰ����
extern "C" _declspec(dllexport)  OutInFor GetInFor();//������ǿ��������Ϣ,��ʼ���ɹ�����ܵ���
extern "C" _declspec(dllexport)  double MoveStepToGetResolPower(Mirror mirror);//�ﾵX�����ƶ�һ������ͼƬ��Ұ���������طֱ���
extern "C" _declspec(dllexport)  void OpenManualMode();//��ʵʱͼ��
extern "C" _declspec(dllexport)  void CloseManualMode();//�ر�ʵʱͼ��
extern "C" _declspec(dllexport)  void ReturnToGetSlide();//��λʶ�𲻳�����ʱ�����˺���������Ƭλ��
extern "C" _declspec(dllexport)  void ClearManualPics(int clearCount);//���ʵʱͼ�����
extern "C" _declspec(dllexport)  void ReturnScanRoi(pair<int, int> scanroi[4]);//��ȡɨ������