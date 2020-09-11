#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<cstring>
using namespace std;
enum operation{Searchsty=1,Searchpig,Searchvariety,quit};
int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int MAXP=1000;
int B_num,S_num1,S_num2,B_sty,S_sty,Sum,sum=0,B_sum,S_sum,B_total,S_total;
double sum_money;
struct pig{
	 string variety;
	double weight;
	int time;
	int sty; 
	int number; 
	pig *next;
};
int Sty[100][11]={0};
int n[100];
pig *Alive=NULL,*Sold=NULL,*Dead=NULL;
operation Menu(); 
int B_initial(pig*);
int S_initial(pig*,int);
pig* pass(pig*);
pig* InsertPig(pig *,pig *);
pig* SellPig(pig *,pig *,pig *);
pig* SearchPig(pig *); 
pig* StorePig(pig* );
void PrintList(pig *);
void SearchS();
void SearchV();
void SearchP();
int B_initial(pig *x){
	int a=Sty[0][10],b=0,i; 
	x->variety="����"; 
	x->time=0;
		for(i=0;i<B_sty;i++){
				if(Sty[i][10]<a){
					a=Sty[i][10];
					b=i;
				}
			}
		x->sty=b;
		Sty[b][10]++;
		for(int i=0;i<10;i++){
			if(Sty[b][i]==0){
				x->number=i;
				Sty[b][i]=1;
				i=10;
			}
		}
		cout<<x->variety<<" "<<x->sty<<" "<<x->number<<endl;
		return 1;	
}
int S_initial(pig *x,int y){
	int a=Sty[B_sty][10],b=B_sty,i;
	if(y==1) x->variety="�󻨰���";
	else x->variety="С����"; 
	x->time=0;
		for(i=B_sty;i<100;i++){
				if(Sty[i][10]<a){
					a=Sty[i][10];
					b=i;
				}
			}
		x->sty=b;
		Sty[b][10]++;
		for(int i=0;i<10;i++){
			if(Sty[b][i]==0){
				x->number=i;
				Sty[b][i]=1;
				i=10;
			}
		}
		cout<<x->variety<<" "<<x->sty<<" "<<x->number<<endl;
		return 1;
}
pig * pass(pig *Alive,int past_time){
	pig *p=Alive;
	srand((unsigned)time(NULL));
	while(p!=NULL){	
		for(int i=0;i<past_time;i++){		
			double y=((double)rand()/RAND_MAX)*(1.2-0.0) +0.0;
			p->weight+=y;
			p->time++;
		}
		p=p->next; 
	}
	return Alive;
}
pig *InsertPig(pig *Alive,pig *x){
	pig *p,*q;
	p=Alive;
	if(Alive==NULL){
		Alive=x;
		x->next=NULL;
		x->number=0;
	} 
	else {
		while((x->sty>p->sty) && (p->next!=NULL)){		
			q=p; 
	 		p=p->next;
		}
		 if(x->sty<=p->sty) 
  {	  if(Alive==p) 
	  { Alive=x;        
		 x->next=p;
	 } 	  
	  else 
	  { q->next=x;
		x->next=p;         
	  }  	  
  } 
  else  
  {  p->next=x;   
     x->next=NULL;
  } 
	return Alive; 
}
}
pig *StorePig(pig *Alive){
	srand((unsigned)time(NULL));
	for(int i=0;i<B_num;i++){
		pig* New=new pig;
		int j=B_initial(New);
		New->weight=((double)rand()/RAND_MAX)*(50.0-20.0)+20.0;
		Alive=InsertPig(Alive,New);
	}
		for(int i=0;i<S_num2;i++){
			pig *New=new pig;
			int j=S_initial(New,2);
			New->weight=((double)rand()/RAND_MAX)*(50.0-20.0)+20.0;
			Alive=InsertPig(Alive,New);
		}
		for(int i=0;i<S_num1;i++){
			pig *New=new pig;
			int j=S_initial(New,1);
			New->weight=((double)rand()/RAND_MAX)*(50.0-20.0)+20.0;
			Alive=InsertPig(Alive,New);
		}
	return Alive;	
	} 	
pig* SellPig(pig *Alive,pig *Sold){
	 
	cout<<"������...\n";
	pig *p,*q,*x,*temp1,*temp2;
	x=Sold;
	while(Sold!=NULL&&x->next!=NULL)
		x=x->next;
	int a=0,b=0,c=0;
	double d,e,f,money;
	p=Alive;
	if(Alive==NULL){
		cout<<"�������û�����ˣ�\n";
		return Alive; 
	} 
	while(p!=NULL){
		if(p->time>365||p->weight>75){
			temp1=p->next;
			temp2=p;
			if(p->variety=="����"){
				a++;
				d=d+p->weight;
				Sty[p->sty][10]--;
				Sty[p->sty][p->number]=0;
			}
			else if(p->variety=="�󻨰���"){
				b++;
				e+=p->weight;	
				Sty[p->sty][10]--;
				Sty[p->sty][p->number]=0;
			}
			else {
				c++;
				f+=p->weight;
				Sty[p->sty][10]--;
				Sty[p->sty][p->number]=0;
			}
			if(Sold==NULL){
				Sold=p;
				x=p;
				Sold->next=NULL;
			}
			else{
				x->next=p;
				p->next=NULL;
			}
			if(temp2==Alive){
				Alive=temp1;
				p=temp1;
			}
			else {
				q->next=temp1;
				p=q->next;
			}
		}
		else {
			q=p;
			p=p->next;
		} 
	}
	
	money=d*30+e*12+f*14;
	money=int(money*100);
	money/=100;
	sum_money+=money;
	cout<<"������"<<a<<"ֻ����"<<b<<"ֻ�󻨰���"<<c<< "ֻС����\n";
	cout<<"�˴γ���׬"<<money<<"Ԫ\n";
	cout<<"��������׬"<<sum_money<<"Ԫ\n"; 
	sum=sum-a-b-c;
	B_sum=B_sum-a;
	S_sum=S_sum-b-c;
	return Alive;
}
void PrintList(pig *Alive){
	pig *p;
	p=Alive;
	if (Alive==NULL)cout<<"������"<<endl; 
	else while (p!=NULL){
		cout<<p->variety<<"������"<<p->sty<<"����Ȧ�У����Ϊ"<<p->number<<",����Ϊ"<<p->weight<<endl;
		p=p->next;
	}
}
operation  Menu(){  
	int choice;
   cout<<endl<<endl;
   cout<<"��Ȧ�����˵�"<<endl;
   cout<<"1 ��ѯ��Ȧ��Ϣ"<<endl;
   cout<<"2 ����ĳһֻ����Ϣ"<<endl;
   cout<<"3 ������������Ϣ"<<endl;
   cout<<"4 �˳�"<<endl;
   cout<<endl<<endl<<"�����빦�����";
   cin>>choice;
   return operation(choice);

}
void SearchS(){
	if(Alive==NULL){
		cout<<"��û�����ˣ�\n";
		return;
	}
	cout<<"������Ҫ��ѯ����Ȧ:\n";
	int a,b=0,c=0;
	string x="0",y="0";
	cin>>a;
	while(a<0||a>99) {
		cout<<"�޴���Ȧ������������\n";
		cin>>a;
	}
	if(Sty[a][10]==0){
		cout<<"����Ȧ��û����\n";
		return;
	}
	pig *p=Alive;
	while(p->next!=NULL){
		if(p->sty!=a);
		else {
			if(x=="0") {
				x=p->variety;
				b++;
			}
			else if(x==p->variety)b++;
			else if(x!=p->variety&&y=="0") {
				y=p->variety;
				c++;
			}	
			else if(y==p->variety)	c++;
		}
		p=p->next;
	}
	if(y=="0")cout<<"����Ȧ����"<<b<<"ֻ"<<x<<endl;
	else cout<< "����Ȧ����"<<b<<"ֻ"<<x<<","<<c<<"ֻ"<<y<<endl;
	return; 
}
void SearchP(){
	pig *p=Alive;
	if(Alive==NULL){
		cout<<"��û�����ˣ�\n";
		return;
	} 
	cout<<"��������������Ȧ����Լ�����\n��Ȧ���:";
	int a,b;
	cin>>a;
	cout<<"\n����:";
	cin>>b; 
	while(a<0||a>99||b<0||b>9){
		cout<<"�����������������";
		cout<<"\n��Ȧ���:";
		cin>>a;
		cout<<"\n����:";
		cin>>b; 
	} 
	while(p->next!=NULL){
		if(p->sty==a&&p->number==b){
			cout<<"����Ϊ"<<p->variety<<",����Ϊ"<<p->weight<<"ǧ��,������" <<p->time<<"��\n";
			return;
		}
		p=p->next;
	}
	cout<<"���޴���...\n"; 
}
void SearchV(){
	pig *p=Alive;
	if(Alive==NULL){
		cout<<"��û�����ˣ�\n";
		return;
	} 
	string a;
	int i=0;
	cout<<"����Ҫ��ѯ���������:\n";
	cin>>a;
	while(p->next!=NULL){
		if(p->variety==a){
			i++;
			cout<<"��"<<i<<"��"<<p->sty<<"����Ȧ��,���Ϊ"<<p->number;
			cout<<",����Ϊ"<<p->weight<<",��������"<<p->time<<"��\n"; 
		}
		p=p->next;
	} 
}
int main(){
begin:	cout<<"��������Ҫ����ĺ����󻨰���С�����������"<<endl<<"����������";
	cin>>B_num;
	cout<<"�󻨰���������";
	cin>>S_num1;
	cout<<"С����������"; 
	cin>>S_num2;
	sum=B_num+S_num1+S_num2,S_sum=S_num1+S_num2,B_sum=B_num;
	while(sum>MAXP){
		cout<<"���޷�������ô����\n";
		cout<<"������������Ҫ����ĺ����󻨰���С�����������"<<endl<<"����������";
		cin>>B_num;
		cout<<"�󻨰���������";
		cin>>S_num1;
		cout<<"С����������"; 
		cin>>S_num2;
		sum=B_num+S_num1+S_num2,S_sum=S_num1+S_num2,B_sum=B_num; 
	}
	float ratio=B_num;
	ratio=ratio/sum;
	B_sty=ratio*100;
	if(B_sty==0)B_sty=1;
	if(B_sty==100)B_sty=99;
	B_total=B_sty*10;
	S_sty=100-B_sty;
	S_total=S_sty*10;
	if(B_total<B_sum||S_total<S_sum){
		cout<<"�����޷�������Ȧ�������¿��ǹ������������\n";
		goto begin;
	}
	Alive=StorePig(Alive);
	cout<<"�����ѽ���\n"; 
	PrintList(Alive);
	time_t timep1;
	struct tm *Nowtime0;
	int past_time;
	time(&timep1);
	Nowtime0=gmtime(&timep1);
	int Lasttime_sec=Nowtime0->tm_sec,Lasttime_min=Nowtime0->tm_min,Lasttime_hour=Nowtime0->tm_hour;
	int a=0;
loop:	if(1){
		cout<<"����1����ѯ�������Ϣ;\n";
		cout<<"������2��������\n";
		cin>>a;
		if(a==1){
			time(&timep1);
			Nowtime0=gmtime(&timep1);
			if(Nowtime0->tm_min<Lasttime_min)
				past_time=(Nowtime0->tm_hour-Lasttime_hour-1)*3600+(Nowtime0->tm_min-Lasttime_min+60)*60+(Nowtime0->tm_sec-Lasttime_sec);
			else 
				past_time=(Nowtime0->tm_hour-Lasttime_hour)*3600+(Nowtime0->tm_min-Lasttime_min)*60+(Nowtime0->tm_sec-Lasttime_sec);
			int n=past_time/90,m=past_time%90;
			cout<<"����һ�β�ѯ�ѹ�"<<past_time<<"��\n"; 
			cout<<"�ڼ乲���й�"<<n<<"�ι������۳���\n";
			for(int i=0;i<=0;i++){
				Alive=pass(Alive,90);
				SellPig(Alive,Sold);
				cout<<"��������Ҫ����ĺ����󻨰���С�����������"<<endl<<"����������";
				cin>>B_num;
				cout<<"�󻨰���������";
				cin>>S_num1;
				cout<<"С����������"; 
				cin>>S_num2;
				sum=sum+B_num+S_num1+S_num2;
				S_sum=S_sum+S_num1+S_num2;
				B_sum=B_sum+B_num;
				while(sum>MAXP||B_sum>B_total||S_sum>S_total){
					sum=sum-B_num-S_num1-S_num2;
					S_sum=S_sum-S_num1-S_num2;
					B_sum=B_sum-B_num;
					cout<<"���޷�������ô����\n";
					cout<<"������������Ҫ����ĺ����󻨰���С�����������"<<endl<<"����������";
					cin>>B_num;
					cout<<"�󻨰���������";
					cin>>S_num1;
					cout<<"С����������"; 
					cin>>S_num2;
					sum=B_num+S_num1+S_num2; 
				}
				Alive=StorePig(Alive);
				PrintList(Alive); 
		}
		 Alive=pass(Alive,past_time);
	}
	else if(a==2) {
		cout<<"��������\nBye";
		goto end;
	}
	else {
		cout<<"�������;\n";
		goto loop;
	}
	operation menu_choice;  
  do 
  {
   menu_choice=Menu(); 
   switch(menu_choice) 
   {
      case Searchsty: cout<<"1 ��ѯ��Ȧ��Ϣ"<<endl<<endl;
		               SearchS(); 
					    break;
	  case  Searchpig: cout<<"2 ����ĳһֻ����Ϣ"<<endl<<endl;
                       SearchP();
					   break;
      case  Searchvariety: cout<<"3 ������������Ϣ"<<endl<<endl;
                       SearchV();
					    break; 
	  case	quit : 
	  default:   	cout<<"������ѯ"<<endl;
	  				time(&timep1);
					Nowtime0=gmtime(&timep1);
					Lasttime_sec=Nowtime0->tm_sec,Lasttime_min=Nowtime0->tm_min,Lasttime_hour=Nowtime0->tm_hour;
	  				goto loop;
   }   
	}while(menu_choice!=quit);
end:   return 0;
}
}
