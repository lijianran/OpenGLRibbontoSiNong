#include "stdafx.h"
#include "Toponology.h"
CToponology::CToponology(void)
{
}


CToponology::~CToponology(void)
{
}

double CToponology::Distance(Point m1,Point m2) //���ص����������ŷ�Ͼ���
{
	return sqrt((m1.x-m2.x)*(m1.x-m2.x)+(m1.y-m2.y)*(m1.y-m2.y));
}

double CToponology::Distance_2(Point m1,Point m2) //���ص����������ŷ�Ͼ���
{
	return ((m1.x-m2.x)*(m1.x-m2.x)+(m1.y-m2.y)*(m1.y-m2.y));
}

double CToponology::cosangle(Point m1,Point m2,Point m3)
{
	return (m2.x-m1.x)*(m2.x-m3.x)+(m2.y-m1.y)*(m2.y-m3.y);
}

double CToponology::multiply(Point sp,Point ep,Point op) 
{ 
	return((sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y)); 
} 

//�ж��߶����߶��Ƿ��ཻ
bool CToponology::intersect(LINESEG u,LINESEG v) 
{ 
	return( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&                     //�ų�ʵ�� 
		(max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&& 
		(max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&& 
		(max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&& 
		(multiply(v.s,u.e,u.s)*multiply(u.e,v.e,u.s)>=0)&&         //����ʵ�� 
		(multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0)); 
} 


bool CToponology::InsideConvexPolygon(int vcount,Point polygon[],Point q) // �����������Σ� 
{ 
	Point *p=new Point; 
	LINESEG *l=new LINESEG; 
	int i; 
	p->x=0;p->y=0; 
	for(i=0;i<vcount;i++) // Ѱ��һ���϶��ڶ����polygon�ڵĵ�p������ζ���ƽ��ֵ 
	{ 
		p->x+=polygon[i].x; 
		p->y+=polygon[i].y; 
	} 
	p->x /= vcount; 
	p->y /= vcount; 

	for(i=0;i<vcount;i++) 
	{ 
		l->s=polygon[i];l->e=polygon[(i+1)%vcount]; 
		if(multiply(*p,l->e,l->s)*multiply(q,l->e,l->s)<=0) /* ��p�͵�q�ڱ�l�����࣬˵����q�϶��ڶ������ */ 
			break; 
	} 
	delete p;
	delete l;
	return (i==vcount); 
} 

bool CToponology::InsideConvexPolygon(int vcount,vector<Point> polygon,Point q) // �����������Σ� 
{ 
	Point *p=new Point; 
	LINESEG *l=new LINESEG; 
	int i; 
	p->x=0;p->y=0; 
	for(i=0;i<vcount;i++) // Ѱ��һ���϶��ڶ����polygon�ڵĵ�p������ζ���ƽ��ֵ 
	{ 
		p->x+=polygon[i].x; 
		p->y+=polygon[i].y; 
	} 
	p->x /= vcount; 
	p->y /= vcount; 

	for(i=0;i<vcount;i++) 
	{ 
		l->s=polygon[i];l->e=polygon[(i+1)%vcount]; 
		if(multiply(*p,l->e,l->s)*multiply(q,l->e,l->s)<=0) /* ��p�͵�q�ڱ�l�����࣬˵����q�϶��ڶ������ */ 
			break; 
	} 
	delete p;
	delete l;
	return (i==vcount); 
} 


//����1��ʾ�ཻ������0��ʾ���ཻ
bool CToponology::CurveInsects(Point Up[],Point Down[],LINESEG u)
{

	//bool flag_up,flag_down;
	//flag_down=flag_up=0;

	//for(int i=0;i<fileLength-1;i++)
	//{
	//	LINESEG l;
	//	l.s=Up[i];
	//	l.e=Up[i+1];
	//	if(intersect(l,u)==1)
	//	{
	//		flag_up=1;
	//		break;
	//	}
	//}

	//for(int i=0;i<fileLength-1;i++)
	//{
	//	LINESEG l;
	//	l.s=Down[i];
	//	l.e=Down[i+1];
	//	if(intersect(l,u)==1)
	//	{
	//		flag_down=1;
	//		break;
	//	}
	//}
	//if(flag_down==0&&flag_up==0)
	//	return 0;
	//else return 1;
	return 0;
}

////�жϵ��Ƿ����ϰ��������ڵģ����ϰ����ڷ���1�����ڷ���0;

//����1��ʾ����ͨ��������0��ʾ����ͨ��

double CToponology::AngleNormalnize1(double phi)
{
	if(phi>2.0*PI)phi=phi-2.0*PI;
	if(phi<0)phi=phi+2.0*PI;
	return phi;
}

double CToponology::AngleNormalnize2(double phi)
{
	while(phi>PI)phi=phi-2.0*PI;
	while(phi<-PI)phi=phi+2.0*PI;
	return phi;
}

double CToponology::AngleNormalnize_jiaodu(double phi)
{
	if(phi>360)phi=phi-360;
	if(phi<0)phi=phi+360;
	return phi/180.0*PI;
}

bool CToponology::PolygonOverPolygon(vector<double>vertX, vector<double>vertY, vector<double>_vertX, vector<double>_vertY)
{//�ж���������Ƿ��ཻ
	//�ж�vert�Ƿ��ж�����_vert��
	for(int i=0;i<=(int)vertX.size()-1;i++)
	{
		//��vert[i]�Ƿ���_vert��
		if(PointInPolygon(_vertX,_vertY,vertX[i],vertY[i]))
		{
			return true;
		}
	}
	//�ж�_vert�Ƿ��ж�����vert��
	for(int i=0;i<=(int)_vertX.size()-1;i++)
	{
		//��_vert[i]�Ƿ���vert��
		if(PointInPolygon(vertX,vertY,_vertX[i],_vertY[i]))
		{
			return true;
		}
	}
	//�ж�vert��_vert�Ƿ����ཻ��
	int n=(int)vertX.size();
	int _n=(int)_vertX.size();
	for(int i=0;i<=n-1;i++)
	{
		for(int j=0;j<=_n-1;j++)
		{
			//�жϱ�(i,i+1)�ͱ�(j,j+1)�Ƿ��ཻ
			if(LineSegOverLineSeg(vertX[i],vertY[i],vertX[(i+1)%n],vertY[(i+1)%n],
				_vertX[j],_vertY[j],_vertX[(j+1)%_n],_vertY[(j+1)%_n]))
			{
				return true;
			}
		}
	}
	return false;
}



bool CToponology::PolygonOverPolygon(vector<Point>vert1, vector<Point>vert2)
{//�ж���������Ƿ��ཻ
	//�ж�vert�Ƿ��ж�����_vert��
	for(int i=0;i<=(int)vert1.size()-1;i++)
	{
		//��vert[i]�Ƿ���_vert��
		if(InsideConvexPolygon(vert2.size(),vert2,vert1[i])==true)
		{
			return true;
		}
	}
	//�ж�_vert�Ƿ��ж�����vert��
	for(int i=0;i<=(int)vert2.size()-1;i++)
	{
		//��vert[i]�Ƿ���_vert��
		if(InsideConvexPolygon(vert1.size(),vert1,vert2[i])==true)
		{
			return true;
		}
	}

	//�ж�vert��_vert�Ƿ����ཻ��
	int n=(int)vert1.size();
	int _n=(int)vert2.size();
	for(int i=0;i<=n-1;i++)
	{
		for(int j=0;j<=_n-1;j++)
		{
			LINESEG u,v;
			u.s.x=vert1[i].x;
			u.s.y=vert1[i].y;
			u.e.x=vert1[(i+1)%n].x;
			u.e.y=vert1[(i+1)%n].y;

			v.s.x=vert2[i].x;
			v.s.y=vert2[i].y;
			v.e.x=vert2[(i+1)%n].x;
			v.e.y=vert2[(i+1)%n].y;

			//�жϱ�(i,i+1)�ͱ�(j,j+1)�Ƿ��ཻ
			if(intersect(u,v)==1)
			{
				return true;
			}
		}
	}
	return false;
}
bool CToponology::LineSegOverLineSeg(double x1,double y1,double x2,double y2,double u1,double v1,double u2,double v2)
{//�ж϶ζ�(x1,y1)-(x2,y2)���߶�(u1,v1)-(u2,v2)�Ƿ��ཻ
	//�ж�(u1,v1)��(u2,v2)�Ƿ���ֱ��(x1,y1)-(x2,y2)��ͬ��
	bool u1v1_separate_u2v2=false;
	float a=(v1-y1)*(x2-x1)-(y2-y1)*(u1-x1);
	float b=(v2-y1)*(x2-x1)-(y2-y1)*(u2-x1);
	if(a*b<0)u1v1_separate_u2v2=true;
	//�ж�(x1,y1)��(x2,y2)�Ƿ���ֱ��(u1,v1)-(u2,v2)��ͬ��
	bool x1y1_separate_x2y2=false;
	a=(y1-v1)*(u2-u1)-(v2-v1)*(x1-u1);
	b=(y2-v1)*(u2-u1)-(v2-v1)*(x2-u1);
	if(a*b<0)x1y1_separate_x2y2=true;
	return x1y1_separate_x2y2*u1v1_separate_u2v2;
}
bool CToponology::PointInPolygon(vector<double>vertX, vector<double>vertY,double x,double y)
{//�жϵ�(x,y)�Ƿ��ڶ����(vertX,vertY)��
	//const double a=0;
	//const long inf=10000;
	const long infi=10000;
	//����ˮƽ���������(x,y)->(xfar,yfar)
	long xfar=-infi;
	long yfar=y;
	double nCross=0;//��������
	int XV=0;//���ߴ����ļ�ֵ��
	vector<double> Hmap;//�߶�ֵ�����ڼ�¼x���������С�ĸ���y���������ߵĴ�С��ϵ
	Hmap.resize((int)vertX.size());
	//�߶�ֵ��
	const int noValue=0;
	const int high=1;
	const int low=2;
	const int even=3;
	//���HLmap
	int n=(int)vertX.size();
	for(int i=0;i<=n-1;i++){
		if(vertX[i]>=x){
			Hmap[i]=noValue;
		}else{
			if(vertY[i]>y)Hmap[i]=high;
			else if(vertY[i]==y)Hmap[i]=even;
			else Hmap[i]=low;
		}
	}
	//����nCross
	for(int i=0;i<=n-1;i++){
		if(Hmap[i]!=even&&Hmap[(i+1)%n]!=even){
			//����ߵ������˵㶼���������ϣ�����Ҫ�ж��Ƿ񴩹�
			bool cross=LineSegOverLineSeg(x,y,xfar,yfar,
				vertX[i],vertY[i],vertX[(i+1)%n],vertY[(i+1)%n]);
			if(cross)nCross++;
		}else if(Hmap[i]==even&&Hmap[(i+1)%n]==even){
			//����ߵ������˵㶼�������ϣ���˱߶���Щ������˵�˻���Ϊһ����
			//���Դ���������Ϊ0
		}else{
			//�����ǡ��һ���˵��������ϣ����Ϊ�������
			//(��һ����֮����ı�Ҳ����Ϊ������Σ����������������ʹճ�һ����)
			nCross+=0.5;
		}	
	}
	//����Hmap���㼫ֵ��
	int nseg=0;//Hmap��!noValue��������
	//֮����Ҫ��¼���ֵ����Ϊ
	//���淽��ֻ����nseg!=0ʱ�ŵõ���Ч���
	//����nseg=0ʱ�������ټ��㣬��ֱ���ж�ΪOUT
	//ע��Hmap��ȫΪnoValue����ȫΪ!noValueʱ����Ϊnseg=0
	int i=0;//����Hmap��ָ��
	while(1){
		//����һ��seg
		//����һ��noValue:!noValue����
		for(;i<=n-1;i++){
			if(Hmap[i]==noValue&&Hmap[(i+1)%n]!=noValue)break;
		}
		if(i<=n-1){//break�����ģ��ҵ���i:i+1������
			nseg++;
			//ͳ��!noValue�ĸ���
			int len=0;
			for(int u=i+1;u<=i+1+n-1;u++){
				if(Hmap[u%n]!=noValue)len++;
				else break;
			}//�õ�len
			//��������[(i+1)%n,(i+1+len-1)%n]�ϵļ�ֵ����
			//Ϊ���ж�����˵㴦�Ǽ�ֵ�㻹�ǹյ���Ҫ�õ���������ھӵ�i��i+1�ĸ߶�ֵ
			//��Hmap[i]
			if(vertY[i]>y)Hmap[i]=high;
			else if(vertY[i]==y)Hmap[i]=even;
			else Hmap[i]=low;
			//��Hmap[(i+1+len)%n]
			if(vertY[(i+1+len)%n]>y)Hmap[(i+1+len)%n]=high;
			else if(vertY[(i+1+len)%n]==y)Hmap[(i+1+len)%n]=even;
			else Hmap[(i+1+len)%n]=low;
			//�߽����
			if(Hmap[i]==even&&Hmap[(i+1)%n]==even)return false;
			if(Hmap[(i+1+len-1)%n]==even&&Hmap[(i+1+len)%n]==even)return false;
			//�м�
			int Hf;
			bool noweven=false;
			for(int j=i+1;j<=i+1+len;j++){//����len+1��Ԫ��
				if(Hmap[j%n]==even){
					if(noweven==false){//��even����
						Hf=Hmap[(j-1)%n];//����evenǰһ��ĸߵ�
						noweven=true;
					}
				}else{
					if(noweven==true){//��even����
						if(Hmap[j%n]==Hf)XV++;//�Ǽ�ֵ
						noweven=false;
					}
				}
			}//��seg�ϵļ�ֵ��ͳ�����
			//�ָ�Hmap[i]��Hmap[(i+1+len)%n]
			Hmap[i]=noValue;
			Hmap[(i+1+len)%n]=noValue;
			//����i
			i=i+1+len;
		}else{//û�ҵ�
			break;
		}
	}
	if(nseg==0){//��nseg=0�����淽������������Ч��,
		//���Դ�ʱ�õ���XV=0Ҳ����Ч���,
		//���ù�����ֱ�ӷ���OUT����
		return false;
	}
	int nRealCross=nCross+XV;//ʵ�ʵĴ�͸��
	if(nRealCross%2==1){
		return true;
	}else{
		return false;
	}
}

short CToponology::MiddlePiont_Shan(double firMidPoint_x,double firMidPoint_y)
{
	static float a_theta =0;
	static int n=1;
	static float angle_previous=0;
	double a;					//a:����ǰ��ת��
	double delt_b;				//delt_b:������ǰ�����Ԥ�鷽��ļн�  Ԥ�鷽�򣺳����������ĺ�Ԥ��������
	const double L=2.5;	;		//���� L:��ǰ�������.�ݶ�Ϊ2.5��
	double Lf;					//Lforward������������Ԥ���ľ���
	const double delt_y=3;		//���� ��ǰ���е�����������ĵľ��룬y������
	double c;					//������ת��
	double kp=1;				//ת������
	double error=0;
	delt_b = atan(firMidPoint_x /(firMidPoint_y));
	Lf = sqrt((firMidPoint_x*firMidPoint_x) + (firMidPoint_y)*(firMidPoint_y));
	a = atan( 2*L*sin(delt_b) / Lf);
	a_theta = a*180.0*15.0/PI;
	short changeangle;
	changeangle=a_theta+550;                          
	return changeangle;

}

	