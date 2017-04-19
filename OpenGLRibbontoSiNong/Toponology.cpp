#include "stdafx.h"
#include "Toponology.h"
CToponology::CToponology(void)
{
}


CToponology::~CToponology(void)
{
}

double CToponology::Distance(Point m1,Point m2) //返回的是两个点的欧氏距离
{
	return sqrt((m1.x-m2.x)*(m1.x-m2.x)+(m1.y-m2.y)*(m1.y-m2.y));
}

double CToponology::Distance_2(Point m1,Point m2) //返回的是两个点的欧氏距离
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

//判断线段与线段是否相交
bool CToponology::intersect(LINESEG u,LINESEG v) 
{ 
	return( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&                     //排斥实验 
		(max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&& 
		(max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&& 
		(max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&& 
		(multiply(v.s,u.e,u.s)*multiply(u.e,v.e,u.s)>=0)&&         //跨立实验 
		(multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0)); 
} 


bool CToponology::InsideConvexPolygon(int vcount,Point polygon[],Point q) // 可用于三角形！ 
{ 
	Point *p=new Point; 
	LINESEG *l=new LINESEG; 
	int i; 
	p->x=0;p->y=0; 
	for(i=0;i<vcount;i++) // 寻找一个肯定在多边形polygon内的点p：多边形顶点平均值 
	{ 
		p->x+=polygon[i].x; 
		p->y+=polygon[i].y; 
	} 
	p->x /= vcount; 
	p->y /= vcount; 

	for(i=0;i<vcount;i++) 
	{ 
		l->s=polygon[i];l->e=polygon[(i+1)%vcount]; 
		if(multiply(*p,l->e,l->s)*multiply(q,l->e,l->s)<=0) /* 点p和点q在边l的两侧，说明点q肯定在多边形外 */ 
			break; 
	} 
	delete p;
	delete l;
	return (i==vcount); 
} 

bool CToponology::InsideConvexPolygon(int vcount,vector<Point> polygon,Point q) // 可用于三角形！ 
{ 
	Point *p=new Point; 
	LINESEG *l=new LINESEG; 
	int i; 
	p->x=0;p->y=0; 
	for(i=0;i<vcount;i++) // 寻找一个肯定在多边形polygon内的点p：多边形顶点平均值 
	{ 
		p->x+=polygon[i].x; 
		p->y+=polygon[i].y; 
	} 
	p->x /= vcount; 
	p->y /= vcount; 

	for(i=0;i<vcount;i++) 
	{ 
		l->s=polygon[i];l->e=polygon[(i+1)%vcount]; 
		if(multiply(*p,l->e,l->s)*multiply(q,l->e,l->s)<=0) /* 点p和点q在边l的两侧，说明点q肯定在多边形外 */ 
			break; 
	} 
	delete p;
	delete l;
	return (i==vcount); 
} 


//返回1表示相交，返回0表示不相交
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

////判断点是否在障碍物（多个）内的，在障碍物内返回1，不在返回0;

//返回1表示不能通过，返回0表示可以通过

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
{//判断两多边形是否相交
	//判断vert是否有顶点在_vert内
	for(int i=0;i<=(int)vertX.size()-1;i++)
	{
		//看vert[i]是否在_vert内
		if(PointInPolygon(_vertX,_vertY,vertX[i],vertY[i]))
		{
			return true;
		}
	}
	//判断_vert是否有顶点在vert内
	for(int i=0;i<=(int)_vertX.size()-1;i++)
	{
		//看_vert[i]是否在vert内
		if(PointInPolygon(vertX,vertY,_vertX[i],_vertY[i]))
		{
			return true;
		}
	}
	//判断vert和_vert是否有相交边
	int n=(int)vertX.size();
	int _n=(int)_vertX.size();
	for(int i=0;i<=n-1;i++)
	{
		for(int j=0;j<=_n-1;j++)
		{
			//判断边(i,i+1)和边(j,j+1)是否相交
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
{//判断两多边形是否相交
	//判断vert是否有顶点在_vert内
	for(int i=0;i<=(int)vert1.size()-1;i++)
	{
		//看vert[i]是否在_vert内
		if(InsideConvexPolygon(vert2.size(),vert2,vert1[i])==true)
		{
			return true;
		}
	}
	//判断_vert是否有顶点在vert内
	for(int i=0;i<=(int)vert2.size()-1;i++)
	{
		//看vert[i]是否在_vert内
		if(InsideConvexPolygon(vert1.size(),vert1,vert2[i])==true)
		{
			return true;
		}
	}

	//判断vert和_vert是否有相交边
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

			//判断边(i,i+1)和边(j,j+1)是否相交
			if(intersect(u,v)==1)
			{
				return true;
			}
		}
	}
	return false;
}
bool CToponology::LineSegOverLineSeg(double x1,double y1,double x2,double y2,double u1,double v1,double u2,double v2)
{//判断段段(x1,y1)-(x2,y2)和线段(u1,v1)-(u2,v2)是否相交
	//判断(u1,v1)和(u2,v2)是否在直线(x1,y1)-(x2,y2)异同侧
	bool u1v1_separate_u2v2=false;
	float a=(v1-y1)*(x2-x1)-(y2-y1)*(u1-x1);
	float b=(v2-y1)*(x2-x1)-(y2-y1)*(u2-x1);
	if(a*b<0)u1v1_separate_u2v2=true;
	//判断(x1,y1)和(x2,y2)是否在直线(u1,v1)-(u2,v2)异同侧
	bool x1y1_separate_x2y2=false;
	a=(y1-v1)*(u2-u1)-(v2-v1)*(x1-u1);
	b=(y2-v1)*(u2-u1)-(v2-v1)*(x2-u1);
	if(a*b<0)x1y1_separate_x2y2=true;
	return x1y1_separate_x2y2*u1v1_separate_u2v2;
}
bool CToponology::PointInPolygon(vector<double>vertX, vector<double>vertY,double x,double y)
{//判断点(x,y)是否在多边形(vertX,vertY)内
	//const double a=0;
	//const long inf=10000;
	const long infi=10000;
	//构造水平向左的射线(x,y)->(xfar,yfar)
	long xfar=-infi;
	long yfar=y;
	double nCross=0;//穿过次数
	int XV=0;//射线穿过的极值数
	vector<double> Hmap;//高度值表，用于记录x坐标比射线小的各点y坐标与射线的大小关系
	Hmap.resize((int)vertX.size());
	//高度值宏
	const int noValue=0;
	const int high=1;
	const int low=2;
	const int even=3;
	//填充HLmap
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
	//计算nCross
	for(int i=0;i<=n-1;i++){
		if(Hmap[i]!=even&&Hmap[(i+1)%n]!=even){
			//如果边的两个端点都不在射线上，则需要判断是否穿过
			bool cross=LineSegOverLineSeg(x,y,xfar,yfar,
				vertX[i],vertY[i],vertX[(i+1)%n],vertY[(i+1)%n]);
			if(cross)nCross++;
		}else if(Hmap[i]==even&&Hmap[(i+1)%n]==even){
			//如果边的两个端点都在射线上，则此边对于些射线来说退化成为一个点
			//所以穿过次数计为0
		}else{
			//如果边恰有一个端点在射线上，则记为穿过半次
			//(另一个与之共点的边也被记为穿过半次，于是两个合起来就凑成一次了)
			nCross+=0.5;
		}	
	}
	//根据Hmap计算极值数
	int nseg=0;//Hmap上!noValue的区段数
	//之所以要记录这个值是因为
	//下面方法只有在nseg!=0时才得到有效结果
	//而当nseg=0时，不用再计算，可直接判断为OUT
	//注：Hmap上全为noValue或者全为!noValue时均认为nseg=0
	int i=0;//遍历Hmap的指针
	while(1){
		//找下一个seg
		//找下一个noValue:!noValue交界
		for(;i<=n-1;i++){
			if(Hmap[i]==noValue&&Hmap[(i+1)%n]!=noValue)break;
		}
		if(i<=n-1){//break出来的，找到了i:i+1即所求
			nseg++;
			//统计!noValue的个数
			int len=0;
			for(int u=i+1;u<=i+1+n-1;u++){
				if(Hmap[u%n]!=noValue)len++;
				else break;
			}//得到len
			//计算区间[(i+1)%n,(i+1+len-1)%n]上的极值个数
			//为了判断区间端点处是极值点还是拐点需要用到区间的外邻居点i和i+1的高度值
			//求Hmap[i]
			if(vertY[i]>y)Hmap[i]=high;
			else if(vertY[i]==y)Hmap[i]=even;
			else Hmap[i]=low;
			//求Hmap[(i+1+len)%n]
			if(vertY[(i+1+len)%n]>y)Hmap[(i+1+len)%n]=high;
			else if(vertY[(i+1+len)%n]==y)Hmap[(i+1+len)%n]=even;
			else Hmap[(i+1+len)%n]=low;
			//边界情况
			if(Hmap[i]==even&&Hmap[(i+1)%n]==even)return false;
			if(Hmap[(i+1+len-1)%n]==even&&Hmap[(i+1+len)%n]==even)return false;
			//中间
			int Hf;
			bool noweven=false;
			for(int j=i+1;j<=i+1+len;j++){//遍历len+1个元素
				if(Hmap[j%n]==even){
					if(noweven==false){//是even上沿
						Hf=Hmap[(j-1)%n];//记下even前一点的高低
						noweven=true;
					}
				}else{
					if(noweven==true){//是even下沿
						if(Hmap[j%n]==Hf)XV++;//是极值
						noweven=false;
					}
				}
			}//本seg上的极值数统计完毕
			//恢复Hmap[i]和Hmap[(i+1+len)%n]
			Hmap[i]=noValue;
			Hmap[(i+1+len)%n]=noValue;
			//更新i
			i=i+1+len;
		}else{//没找到
			break;
		}
	}
	if(nseg==0){//若nseg=0，上面方法根本就是无效的,
		//所以此时得到的XV=0也是无效结果,
		//不用管它，直接返回OUT即可
		return false;
	}
	int nRealCross=nCross+XV;//实际的穿透数
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
	double a;					//a:车辆前轮转角
	double delt_b;				//delt_b:车辆当前方向和预瞄方向的夹角  预瞄方向：车两后轮中心和预瞄点的连线
	const double L=2.5;	;		//常量 L:车前后车轮轴距.暂定为2.5米
	double Lf;					//Lforward，后轮中心与预瞄点的距离
	const double delt_y=3;		//常量 车前杠中点和两后轮中心的距离，y方向上
	double c;					//方向盘转角
	double kp=1;				//转角增益
	double error=0;
	delt_b = atan(firMidPoint_x /(firMidPoint_y));
	Lf = sqrt((firMidPoint_x*firMidPoint_x) + (firMidPoint_y)*(firMidPoint_y));
	a = atan( 2*L*sin(delt_b) / Lf);
	a_theta = a*180.0*15.0/PI;
	short changeangle;
	changeangle=a_theta+550;                          
	return changeangle;

}

	