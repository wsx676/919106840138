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
	x->variety="黑猪"; 
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
	if(y==1) x->variety="大花白猪";
	else x->variety="小花猪"; 
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
	 
	cout<<"交易中...\n";
	pig *p,*q,*x,*temp1,*temp2;
	x=Sold;
	while(Sold!=NULL&&x->next!=NULL)
		x=x->next;
	int a=0,b=0,c=0;
	double d,e,f,money;
	p=Alive;
	if(Alive==NULL){
		cout<<"你的猪场里没有猪了！\n";
		return Alive; 
	} 
	while(p!=NULL){
		if(p->time>365||p->weight>75){
			temp1=p->next;
			temp2=p;
			if(p->variety=="黑猪"){
				a++;
				d=d+p->weight;
				Sty[p->sty][10]--;
				Sty[p->sty][p->number]=0;
			}
			else if(p->variety=="大花白猪"){
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
	cout<<"共卖出"<<a<<"只黑猪，"<<b<<"只大花白猪，"<<c<< "只小花猪\n";
	cout<<"此次出售赚"<<money<<"元\n";
	cout<<"开厂至今共赚"<<sum_money<<"元\n"; 
	sum=sum-a-b-c;
	B_sum=B_sum-a;
	S_sum=S_sum-b-c;
	return Alive;
}
void PrintList(pig *Alive){
	pig *p;
	p=Alive;
	if (Alive==NULL)cout<<"空链表"<<endl; 
	else while (p!=NULL){
		cout<<p->variety<<"储存在"<<p->sty<<"号猪圈中，编号为"<<p->number<<",体重为"<<p->weight<<endl;
		p=p->next;
	}
}
operation  Menu(){  
	int choice;
   cout<<endl<<endl;
   cout<<"猪圈操作菜单"<<endl;
   cout<<"1 查询猪圈信息"<<endl;
   cout<<"2 查找某一只猪信息"<<endl;
   cout<<"3 查找猪种类信息"<<endl;
   cout<<"4 退出"<<endl;
   cout<<endl<<endl<<"请输入功能序号";
   cin>>choice;
   return operation(choice);

}
void SearchS(){
	if(Alive==NULL){
		cout<<"你没有猪了！\n";
		return;
	}
	cout<<"输入需要查询的猪圈:\n";
	int a,b=0,c=0;
	string x="0",y="0";
	cin>>a;
	while(a<0||a>99) {
		cout<<"无此猪圈，请重新输入\n";
		cin>>a;
	}
	if(Sty[a][10]==0){
		cout<<"该猪圈中没有猪！\n";
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
	if(y=="0")cout<<"该猪圈中有"<<b<<"只"<<x<<endl;
	else cout<< "该猪圈中有"<<b<<"只"<<x<<","<<c<<"只"<<y<<endl;
	return; 
}
void SearchP(){
	pig *p=Alive;
	if(Alive==NULL){
		cout<<"你没有猪了！\n";
		return;
	} 
	cout<<"请输入猪所在猪圈编号以及猪编号\n猪圈编号:";
	int a,b;
	cin>>a;
	cout<<"\n猪编号:";
	cin>>b; 
	while(a<0||a>99||b<0||b>9){
		cout<<"编号有误，请重新输入";
		cout<<"\n猪圈编号:";
		cin>>a;
		cout<<"\n猪编号:";
		cin>>b; 
	} 
	while(p->next!=NULL){
		if(p->sty==a&&p->number==b){
			cout<<"该猪为"<<p->variety<<",体重为"<<p->weight<<"千克,已饲养" <<p->time<<"天\n";
			return;
		}
		p=p->next;
	}
	cout<<"查无此猪...\n"; 
}
void SearchV(){
	pig *p=Alive;
	if(Alive==NULL){
		cout<<"你没有猪了！\n";
		return;
	} 
	string a;
	int i=0;
	cout<<"输入要查询的猪的种类:\n";
	cin>>a;
	while(p->next!=NULL){
		if(p->variety==a){
			i++;
			cout<<"猪"<<i<<"在"<<p->sty<<"号猪圈中,编号为"<<p->number;
			cout<<",体重为"<<p->weight<<",已饲养了"<<p->time<<"天\n"; 
		}
		p=p->next;
	} 
}
int main(){
begin:	cout<<"请输入需要购买的黑猪、大花白猪、小花猪的数量："<<endl<<"黑猪数量：";
	cin>>B_num;
	cout<<"大花白猪数量：";
	cin>>S_num1;
	cout<<"小花猪数量："; 
	cin>>S_num2;
	sum=B_num+S_num1+S_num2,S_sum=S_num1+S_num2,B_sum=B_num;
	while(sum>MAXP){
		cout<<"你无法饲养这么多猪！\n";
		cout<<"请重新输入需要购买的黑猪、大花白猪、小花猪的数量："<<endl<<"黑猪数量：";
		cin>>B_num;
		cout<<"大花白猪数量：";
		cin>>S_num1;
		cout<<"小花猪数量："; 
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
		cout<<"有猪无法放入猪圈，请重新考虑购买猪的数量；\n";
		goto begin;
	}
	Alive=StorePig(Alive);
	cout<<"养猪场已建立\n"; 
	PrintList(Alive);
	time_t timep1;
	struct tm *Nowtime0;
	int past_time;
	time(&timep1);
	Nowtime0=gmtime(&timep1);
	int Lasttime_sec=Nowtime0->tm_sec,Lasttime_min=Nowtime0->tm_min,Lasttime_hour=Nowtime0->tm_hour;
	int a=0;
loop:	if(1){
		cout<<"输入1来查询猪场相关信息;\n";
		cout<<"或输入2结束程序\n";
		cin>>a;
		if(a==1){
			time(&timep1);
			Nowtime0=gmtime(&timep1);
			if(Nowtime0->tm_min<Lasttime_min)
				past_time=(Nowtime0->tm_hour-Lasttime_hour-1)*3600+(Nowtime0->tm_min-Lasttime_min+60)*60+(Nowtime0->tm_sec-Lasttime_sec);
			else 
				past_time=(Nowtime0->tm_hour-Lasttime_hour)*3600+(Nowtime0->tm_min-Lasttime_min)*60+(Nowtime0->tm_sec-Lasttime_sec);
			int n=past_time/90,m=past_time%90;
			cout<<"距上一次查询已过"<<past_time<<"天\n"; 
			cout<<"期间共进行过"<<n<<"次购买与售出；\n";
			for(int i=0;i<=0;i++){
				Alive=pass(Alive,90);
				SellPig(Alive,Sold);
				cout<<"请输入需要购买的黑猪、大花白猪、小花猪的数量："<<endl<<"黑猪数量：";
				cin>>B_num;
				cout<<"大花白猪数量：";
				cin>>S_num1;
				cout<<"小花猪数量："; 
				cin>>S_num2;
				sum=sum+B_num+S_num1+S_num2;
				S_sum=S_sum+S_num1+S_num2;
				B_sum=B_sum+B_num;
				while(sum>MAXP||B_sum>B_total||S_sum>S_total){
					sum=sum-B_num-S_num1-S_num2;
					S_sum=S_sum-S_num1-S_num2;
					B_sum=B_sum-B_num;
					cout<<"你无法饲养这么多猪！\n";
					cout<<"请重新输入需要购买的黑猪、大花白猪、小花猪的数量："<<endl<<"黑猪数量：";
					cin>>B_num;
					cout<<"大花白猪数量：";
					cin>>S_num1;
					cout<<"小花猪数量："; 
					cin>>S_num2;
					sum=B_num+S_num1+S_num2; 
				}
				Alive=StorePig(Alive);
				PrintList(Alive); 
		}
		 Alive=pass(Alive,past_time);
	}
	else if(a==2) {
		cout<<"结束程序\nBye";
		goto end;
	}
	else {
		cout<<"输入错误;\n";
		goto loop;
	}
	operation menu_choice;  
  do 
  {
   menu_choice=Menu(); 
   switch(menu_choice) 
   {
      case Searchsty: cout<<"1 查询猪圈信息"<<endl<<endl;
		               SearchS(); 
					    break;
	  case  Searchpig: cout<<"2 查找某一只猪信息"<<endl<<endl;
                       SearchP();
					   break;
      case  Searchvariety: cout<<"3 查找猪种类信息"<<endl<<endl;
                       SearchV();
					    break; 
	  case	quit : 
	  default:   	cout<<"结束查询"<<endl;
	  				time(&timep1);
					Nowtime0=gmtime(&timep1);
					Lasttime_sec=Nowtime0->tm_sec,Lasttime_min=Nowtime0->tm_min,Lasttime_hour=Nowtime0->tm_hour;
	  				goto loop;
   }   
	}while(menu_choice!=quit);
end:   return 0;
}
}
