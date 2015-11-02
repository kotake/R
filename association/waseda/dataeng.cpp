/*アプリオリアルゴリズム*/

#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>


void shokisetei();
void aprior();
void step1(int);
void Candi(int);
void Join_Step(int);
void Prune_Step(int);
void Large(int);
void kakusindo();
void teian1();
void teian2(int);
void entropy();

int L[15][30000][15];//ラージアイテム
int C[15][40000][15];//候補アイテム
int count[15][40001];//出現カウント
int n;//アイテム数
int m;//トランザクション数
int Ls[15];//ラージアイテム合計数
int Cs[15];//候補アイテム合計数
int suu=0;//属性数
int k=1;//ステップ数
int de;//デフォルトの値
int answer;//確信度を計算するかどうか
int It[100];//属性内のアイテム数
int Itsum[100];//属性内のアイテム数合計
int Csum=0;//候補アイテム数の合計
int Lsum=0;//ラージアイテム数の合計
float minsup;//最小支持度
float mincon;//最小確信度
float t_minsup;//提案の最小支持度
float tekiyou;//どの手法を適用するか(0：従来,1:最大,2:エントロピー）
float zokusei_sum=0;//属性値数のカウントの合計
float zoku;//属性値数のカウント
float p[100];//出現確率
float S;//スケール
float e[100];//属性のエントロピー

#define FILENAME1 "mushroom.txt"
#define FILENAME2 "out.txt"
#define FILENAME3 "zokusei.txt"

#define DISP  0
#define DISP2 0
#define DISP3 0
#define OUT  0
#define OUT2 0
#define OUT3 0
#define OUTL  0
#define OUTL2 0
#define OUTkakusin 0
#define OUTkakusinF 1

FILE *stream2;


//メイン
int main()
{	
	stream2=fopen(FILENAME2,"wt");

	shokisetei();
	teian1();
	aprior();

	fprintf(stream2,"Goukeikouhoaitemusuu＝%d ",Csum);
	fprintf(stream2,"goukei＝%d\n",Lsum);
	//	fprintf(stream2,"平均属性値数＝%f\n",zokusei_sum/Lsum);
	k=k-1;
	kakusindo();

	fclose(stream2);
}


//エントロピーの計算
void entropy()//エントロピー計算関数
{
	int i,j,zoku_sum=1;
	float y=0,sum;

	/*  int v;
		for(v=1;v<=n;v++)
		{
		printf("p[%d]=%f \n",v,float(count[1][v])/float(m));
		}*/

	for(i=1;i<=suu;i++)
	{
		sum=0;
		for(j=zoku_sum;j<zoku_sum+It[i];j++)
		{
			//printf("%d ",j);
			if(count[1][j]!=0)
			{
				sum=-(float(count[1][j])/float(m))*(float(log(float(count[1][j])/float(m))/log(2.0)))+sum;
				//printf("%f ",sum);
			}		
		}
		//printf("e[%d]=%f \n",i,sum);
		e[i]=sum;
		zoku_sum=zoku_sum+It[i];
	}
}


//////////////////////提案の最小支持度minsup-
void teian1()//属性数の認識
{
	int j,keta,y,p,q,a[5];
	char string[5];
	FILE *zokusei;

	zokusei=fopen(FILENAME3,"rt");
	if(!zokusei)
	{
		//printf("ファイルがありません。\n");
		exit(1);
	}

	Itsum[1]=0;

	while(fgets(string,5,zokusei)!=NULL)//文字(数値データ)を数値に変換
	{
		suu=suu+1;
		It[suu]=0;
		keta=0;

		for(j=0;string[j]!='\n';j++)//何桁か？
		{
			keta=keta+1;
			a[keta]=string[j]-48;
			//			printf("%d ",a[keta]);
			//			fprintf(stream2,"%d ",a[keta]);			
		}

		//		printf("   桁＝%d  ",keta);
		//		fprintf(stream2,"   桁＝%d  j=%d  ",keta,j);

		for(y=1;y<=keta;y++)
		{
			q=1;
			for(p=1;p<y;p++)
			{
				q=q*10;
			}
			It[suu]=It[suu]+a[keta-y+1]*q;
			//			printf("  %d  ",a[keta-y]*q);
		}

		Itsum[suu]=Itsum[suu-1]+It[suu];
		//		printf("%d\n",It[suu]);
		//		fprintf(stream2,"It[%d]=%d\n",suu,It[suu]);
		//		fprintf(stream2,"Itsum[%d]=%d\n",suu,Itsum[suu]);
	}

	fclose(zokusei);
}


void teian2(int i)//C[k][i][]のminsup'の計算
{
	int j,jj;
	float A=0;//出現度
	float H=0;//エントロピー

	S=float(1.0);
	zoku=0;

	for(j=1;j<=k;j++)//ｱｲﾃﾑﾙｰﾌﾟ
	{
		for(jj=1;jj<=suu;jj++)//どの属性に所属するか？
		{
			//			fprintf(stream2,"%d<%d<=%d\n",Itsum[jj-1],C[k][i][j],Itsum[jj]);
			if( (Itsum[jj-1]<C[k][i][j]) && (C[k][i][j]<=Itsum[jj]) )//jj番目の属性に所属する
			{
				if(tekiyou==0 || tekiyou==1)
				{
					A=float(2.0)/float(It[jj]);
					A=(A-float(1.0))*tekiyou+float(1.0);//従来と最大の適用選択
				}

				if(tekiyou==2)
				{
					H=float(2)/float(pow(2,e[jj]));//jj番目の属性のエントロピーを適用
				}

				zoku=zoku+float(It[jj]);//あまり意味はない

				//				printf("%f→%f\n",2.0/It[jj],A);
				//				fprintf(stream2,"%f→%f\n",2.0/It[jj],A);
				//				fprintf(stream2,"A=%f ",A);
			}
		}

		////////属性値数の最大のものを採用する。
		if(tekiyou==0 || tekiyou==1)
		{
			if(S>A)
			{
				S=A;
			}
		}

		////////エントロピーを計算する
		if(tekiyou==2)
		{
			if(S>H)
			{
				S=H;
			}
		}

		//		fprintf(stream2,"S=%f\n",S);
	}

	zoku=zoku/k;//あまり意味はない

	t_minsup=minsup*S;
	//	fprintf(stream2,"t_minsup=%f\n",t_minsup);
}


//アプリオリ
// C():候補ｱｲﾃﾑ集合　L():ﾗｰｼﾞｱｲﾃﾑ集合
// k:ｽﾃｯﾌﾟ数　n:ｱｲﾃﾑ数　m:ﾄﾗﾝｻﾞｸｼｮﾝ数
// Ls:ﾗｰｼﾞｱｲﾃﾑのﾙｰﾙ数　Cs:候補ｱｲﾃﾑのﾙｰﾙ数
void aprior()
{
	step1(k);

	k=2;
	do//ｽﾃｯﾌﾟﾙｰﾌﾟ
	{
		Candi(k);
		Large(k);
		k=k+1;
		//		printf("\n%d\n",Ls[k-1]);
	}
	while(Ls[k-1]!=0);
}


//step1
void step1(int k)
{
	int i,ii,j,p;
	char string[5000];

	FILE *stream1;

	stream1=fopen(FILENAME1,"rt");
	if(!stream1)
	{
		//printf("ファイルがありません。\n");
		exit(1);
	}

	for(ii=0;ii<=5000;ii++)
	{
		count[1][ii]=0;
	}

	m=1;
	while(fgets(string,5000,stream1)!=NULL)//ﾄﾗﾝｻﾞｸｼｮﾝﾙｰﾌﾟ//一行読み込み
	{
		n=1;
		while(string[n-1]!=10)//ｱｲﾃﾑﾙｰﾌﾟ
		{
			//			printf("%c",string[n-1]);
			if(string[n-1]==49)
			{
				count[1][n]=count[1][n]+1;
			}

			//			printf("%f",count[1][n]);
			n=n+1;
			if(n==129)
			{
				break;
			}

		}
		n=n-1;
		m=m+1;
	}

	m=m-1;

	//printf("ｱｲﾃﾑ数=%d\n",n);
	fprintf(stream2,"item_number=%d\n",n);

	//printf("ﾄﾗﾝｻﾞｸｼｮﾝ数=%d\n",m);
	fprintf(stream2,"transaction_number=%d\n",m);

	for(p=1;p<=n;p++)
	{
		C[1][p][1]=p;
	}
	Cs[1]=n;

	//printf("第１ｽﾃｯﾌﾟのﾗｰｼﾞｱｲﾃﾑ\n");
#if OUT
	fprintf(stream2,"first_step_large_item\n");
#endif

	if(tekiyou==2)
	{
		entropy();//エントロピーの計算
		for(j=1;j<=suu;j++)
		{
			fprintf(stream2,"entropy[%d]=%f \n",j,e[j]);
		}
	}

	Ls[1]=0;
	for(i=1;i<=n;i++)//表示
	{
		teian2(i);
		//		fprintf(stream2,"\n");

		if(t_minsup<=float(count[1][i])/float(m))
		{
			Ls[k]=Ls[k]+1;
			L[k][Ls[k]][1]=i;

			zokusei_sum=zokusei_sum+zoku;

			//			printf("zokusei_sum=%f\n",zokusei_sum);
			//			fprintf(stream2,"zokusei_sum=%f\n",zokusei_sum);

#if DISP
			//printf("%d番目のﾗｰｼﾞｱｲﾃﾑ集合%d=%f\n",Ls[1],L[k][Ls[k]][1],1.0*count[1][i]/m);
#endif
#if OUTL	
			fprintf(stream2,"%dth_step_large_item_syuugou %d=%f(minsup':%f)",Ls[1],L[k][Ls[k]][1],1.0*count[1][i]/m,t_minsup);
			if(1.0*count[1][i]/m<minsup)
			{
				fprintf(stream2,"***");
			}
			fprintf(stream2,"\n");
#endif
			count[1][Ls[1]]=count[1][i];
		}
	}

	Csum=n;
	Lsum=Ls[1];

	//printf("第１ｽﾃｯﾌﾟの候補ｱｲﾃﾑ数=%d\n",n);
	fprintf(stream2," first_step_item_kouho_number =%d ",n);

	//printf("第１ｽﾃｯﾌﾟのﾗｰｼﾞｱｲﾃﾑ数=%d\n",Ls[1]);
	fprintf(stream2,"\n first_step_large_item_number=%d\n",Ls[1]);

	fclose(stream1);
}



//候補ｱｲﾃﾑ集合
void Candi(int k)
{
	de=0;

	Join_Step(k);
	Prune_Step(k);

}


///////////////////////Join Step
void Join_Step(int k)
{
	int i,p,q,r,rr,hh,match;

	//printf("第%dｽﾃｯﾌﾟの候補ｱｲﾃﾑ集合\n",k);
#if OUT2
	fprintf(stream2," %dth_step_item_kouho_syugou\n",k);
#endif

	for(p=1;p<=Ls[k-1]-1;p++)//1つ目のｱｲﾃﾑ集合
	{
		for(q=p+1;q<=Ls[k-1];q++)//２つ目のｱｲﾃﾑ集合
		{
			match=0;	
			for(i=1;i<=k-2;i++)//何個目のｱｲﾃﾑか？
			{
				if(L[k-1][p][i]!=L[k-1][q][i])
				{
					//                  printf("%d %d\n",p,q);
					break;	
				}		
				match=match+1;
			}

			if(match==k-2 || k==2)
			{
				if(L[k-1][p][k-1]<L[k-1][q][k-1])
				{
					de=de+1;
					////////////////表示
					//	printf("%d番目のdeｱｲﾃﾑ集合=",de);

					for(hh=1;hh<=k-1;hh++)
					{
						C[k][de][hh]=L[k-1][p][hh];
						//		printf("%d,",C[k][de][hh]);
					}

					C[k][de][k]=L[k-1][q][k-1];
					//	printf("%d\n",C[k][de][k]);
				}
			}
		}
	}

	if(k==2)
	{

		for(r=1;r<=de;r++)
		{
#if DISP2
			//printf("%d番目の候補ｱｲﾃﾑ集合=",r);
#endif
#if OUT2
			fprintf(stream2," %dth_item_kouho_syugou=",r);
#endif
			for(rr=1;rr<=k;rr++)
			{
#if DISP2
				//printf("%d,",C[k][r][rr]);
#endif
#if OUT2
				fprintf(stream2,"%d,",C[k][r][rr]);
#endif
			}
#if DISP2
			printf("\n");
#endif
#if OUT2
			fprintf(stream2,"\n");
#endif
		}

		Cs[k]=de;
		Csum=Csum+de;

		fprintf(stream2," second_step_item_kouho_number＝%d\n",Cs[k]);
	}
}


///////////////////Prune Step
void Prune_Step(int k)
{
	int ii,jj,pp,qq,iii,onaji,chech,zenonaji,junban=0;

	if(k!=2)
	{
		for(jj=1;jj<=de;jj++)//候補ｱｲﾃﾑﾙｰﾌﾟ
		{
			zenonaji=0;
			for(pp=1;pp<=k-2;pp++)//取り除くｱｲﾃﾑ
			{
				for(qq=1;qq<=Ls[k-1];qq++)//k-１のﾗｰｼﾞｱｲﾃﾑ集合検索
				{
					onaji=0;
					chech=0;
					//					printf("%d,%d  ",jj,qq);

					for(ii=1;ii<=k;ii++)//ｱｲﾃﾑ番号
					{
						if(ii!=pp)//取り除くのと同じでないなら
						{

							chech=chech+1;
							if(L[k-1][qq][chech]!=C[k][jj][ii])
							{
								break;
							}

							onaji=onaji+1;
						}
					}

					if(onaji==k-1)//すっかり同じﾗｰｼﾞｱｲﾃﾑ
					{
						zenonaji=zenonaji+1;
						break;
					}
				}
			}

			if(zenonaji==k-2)
			{
				junban=junban+1;
#if DISP3
				//printf("%d番目の候補ｱｲﾃﾑ集合",junban);
#endif
#if OUT3
				fprintf(stream2," %d th_item_kouho_syugo",junban);
#endif
				for(iii=1;iii<=k;iii++)
				{
					C[k][junban][iii]=C[k][jj][iii];
#if DISP3
					//printf("%d,",C[k][junban][iii]);
#endif
#if OUT3
					fprintf(stream2,"%d,",C[k][junban][iii]);
#endif
				}
#if DISP3
				printf("\n");
#endif
#if OUT3
				fprintf(stream2,"\n");
#endif
			}
		}

		Cs[k]=junban;
		Csum=Csum+Cs[k];

		//printf("第%dｽﾃｯﾌﾟの候補ｱｲﾃﾑ集合数＝%d\n",k,Cs[k]);
		fprintf(stream2," %dth_step_item_kouho_syugousuu=%d\n",k,Cs[k]);
	}
}



//ﾗｰｼﾞｱｲﾃﾑ集合
void Large(int k)
{
	int i,ii,j,jj,v,ari;
	char string2[5000];

	FILE *stream11;

	stream11=fopen(FILENAME1,"rt");

	if(!stream11)
	{
		//	printf("ファイルがありません。\n");
		exit(1);
	}

	for(v=1;v<=40001;v++)
	{
		count[k][v]=0;
	}

	//printf("第%dｽﾃｯﾌﾟのﾗｰｼﾞｱｲﾃﾑ集合\n",k);
	////////////////////////カウント

	while(fgets(string2,5000,stream11)!=NULL)//ﾄﾗﾝｻﾞｸｼｮﾝﾙｰﾌﾟ
	{
		//		printf("%c",string2[1]);
		for(ii=1;ii<=Cs[k];ii++)//候補ｱｲﾃﾑﾙｰﾌﾟ
		{
			ari=0;
			for(jj=1;jj<=k;jj++)//ｱｲﾃﾑﾙｰﾌﾟ
			{
				//				printf("%c ",string2[C[k][ii][jj]-1]);

				if(string2[C[k][ii][jj]-1]!='1')
				{
					break;
				}

				ari=ari+1;
			}

			//			printf("ari=%d ",ari);

			if(ari==k)
			{
				count[k][ii]=count[k][ii]+1;
			}
			//			printf("%d=%d  ",ii,count[k][ii]);
		}
		//		printf("\n");
	}
	////////////////////最小支持度絞込み
	Ls[k]=0;
	for(i=1;i<=Cs[k];i++)//候補アイテム集合ループ
	{
		teian2(i);//minsup→t_minsup
		//		fprintf(stream2,"\n");

		if(t_minsup<=1.0*count[k][i]/m)
		{
			Ls[k]=Ls[k]+1;

			zokusei_sum=zokusei_sum+zoku;

			//			printf("zokusei_sum=%f\n",zokusei_sum);
			//			fprintf(stream2,"zokusei_sum=%f\n",zokusei_sum);

#if DISP
			//	printf("%d番目のﾗｰｼﾞｱｲﾃﾑ集合",Ls[k]);
#endif
#if OUTL2
			fprintf(stream2," %dth_large_item_syugo",Ls[k]);
#endif
			for(j=1;j<=k;j++)
			{
				L[k][Ls[k]][j]=C[k][i][j];
#if DISP
				printf("%d,",L[k][Ls[k]][j]);
#endif
#if OUTL2
				fprintf(stream2,"%d,",L[k][Ls[k]][j]);
#endif
			}
#if DISP
			printf("=%f\n",1.0*count[k][i]/m);
#endif
#if OUTL2
			fprintf(stream2,"=%f(minsup':%f)",1.0*count[k][i]/m,t_minsup);
			if(1.0*count[k][i]/m<minsup)
			{
				fprintf(stream2,"***");
			}
			fprintf(stream2,"\n");
#endif
			count[k][Ls[k]]=count[k][i];
		}
	}

	Lsum=Lsum+Ls[k];

	//printf("第%dｽﾃｯﾌﾟのﾗｰｼﾞｱｲﾃﾑ数=%d\n",k,Ls[k]);
	fprintf(stream2," %dth_step_large_item_number=%d\n",k,Ls[k]);

	fclose(stream11);
}



//確信度
void kakusindo()
{
	int i,j,ii,jj,iii,jjj,flag;
	int match,p,q,pp,qq;
	int sum=0,kazu=0,h_zoku[16];
	double zokusum=0;
	float goukei_kaku,goukei_siji;

	goukei_siji=float(0.0);
	goukei_kaku=float(0.0);

	if(answer==0)
	{
		exit(1);
	}

	for(iii=1;iii<=15;iii++)
	{
		h_zoku[iii]=0;
	}

	printf("Saisho-kakushindo wo mitasu rule\n");
	fprintf(stream2,"\n Saisho-kakushindo wo mitasu rule\n");

#if OUTkakusinF
	fprintf(stream2,"zyouken-bu -> ketsuron-bu = [shijido, kakushindo] \n");
#endif

	for(i=2;i<=k;i++)//ｽﾃｯﾌﾟﾙｰﾌﾟ
	{
		for(j=1;j<=Ls[i];j++)//ｱｲﾃﾑ集合ﾙｰﾌﾟL[i][j][]
		{
			for(p=1;p<=i-1;p++)//前提部の個数ﾙｰﾌﾟ
			{				
				for(q=1;q<=Ls[p];q++)//比較ﾗｰｼﾞｱｲﾃﾑ集合のﾙｰﾌﾟ
				{
					match=0;
					for(ii=1;ii<=p;ii++)//比較ｱｲﾃﾑﾙｰﾌﾟ
					{
						for(jj=1;jj<=i;jj++)//ｱｲﾃﾑﾙｰﾌﾟ
						{
							if(L[i][j][jj]==L[p][q][ii])
							{
								match=match+1;
								break;
							}
						}

						if(match==p)
						{
							if(mincon<=1.0*count[i][j]/count[p][q])
							{
								sum=sum+1;
								h_zoku[i]=h_zoku[i]+1;

								for(pp=1;pp<=p;pp++)
								{
#if OUTkakusin
									printf("%3d ",L[p][q][pp]);
#endif
#if OUTkakusinF
									fprintf(stream2,"%3d ",L[p][q][pp]);
#endif
								}
#if OUTkakusin
								printf("→");
#endif
#if OUTkakusinF
								fprintf(stream2,"→");
#endif

								for(qq=1;qq<=i;qq++)
								{
#if OUTkakusin
									printf("%3d ",L[i][j][qq]);
#endif
#if OUTkakusinF
									flag=0;
									for(pp=1;pp<=p;pp++){
										if(L[i][j][qq]==L[p][q][pp]){
											flag=1; break;
										}
									}
									if(flag==0) fprintf(stream2,"%3d ",L[i][j][qq]);
#endif
								}
#if OUTkakusin
								printf("=[%f,%f]",1.0*count[i][j]/m,1.0*count[i][j]/count[p][q]);
#endif
#if OUTkakusinF
								fprintf(stream2,"=[%f,%f]",1.0*count[i][j]/m,1.0*count[i][j]/count[p][q]);
#endif
								if(1.0*count[i][j]/m<minsup)
								{
#if OUTkakusinF
									fprintf(stream2,"***");
#endif
									kazu=kazu+1;
								}
#if OUTkakusin
								printf("\n");
#endif
#if OUTkakusinF
								fprintf(stream2,"\n");
#endif

								goukei_siji=goukei_siji+float(1.0*count[i][j]/m);
								goukei_kaku=goukei_kaku+float(count[i][j])/float(count[p][q]);

							}
						}

					}
				}
			}
		}
	}

	fprintf(stream2,"\n");
	fprintf(stream2,"Saisho-kakushindo = %d  \n",sum);
	//	fprintf(stream2,"提案手法によって抽出されたルール数＝%d\n",kazu);
	fprintf(stream2,"Heikin-shijido = %f ",goukei_siji/sum);
	fprintf(stream2,"Heikin-kakushindo = %f\n",goukei_kaku/sum);
	for(jjj=2;jjj<=15;jjj++)
	{
		//		fprintf(stream2,"%d個のルール数＝%d\n",jjj,h_zoku[jjj]);
		zokusum=zokusum+jjj*h_zoku[jjj];
	}
	//	fprintf(stream2,"平均ルール数＝%f",float(zokusum)/float(sum));

}



//初期設定
void shokisetei()
{

	printf("Apriori Algorithm de soukan-rule no tyuusyutu\n");

	printf("Input Saisho-shijido (0-1)\n");
	scanf("%f",&minsup);
	if(minsup>1.0)
	{
		printf("Input Saisho-shijido again (0-1)\n");
		exit(1);
	}

	printf("Input Saisho-kakushindo (0-1)\n");
	scanf("%f",&mincon);
	if(mincon>1.0)
	{
		printf("Input Saisho-kakushindo again (0-1)\n");
		exit(1);
	}

	//	printf("どの手法を適用しますか？\n");
	//	printf("従来手法：０　,属性値最大手法：１　,エントロピー手法：２\n");
	//	scanf("%f",&tekiyou);
	tekiyou=0;
	if(tekiyou!=0.0 && tekiyou!=1.0 && tekiyou!=2.0)
	{	printf("Tekiyo-shuho wo irenaosite kudasai \n");
		exit(1);
	}

	//	printf("確信度を計算しますか？（はい：１,いいえ：０）");
	//	scanf("%d",&answer);
	answer=1;

	printf("Saisho-shijido = %f Saisho-kakushindo = %f \n",minsup,mincon);
	fprintf(stream2,"Saisho-shijido = %f Saisho-kakushindo = %f \n",minsup,mincon);

}
