#include <stdio.h>

#define SENTE 1
#define GOTE -1
#define NONE 0
#define HINT 2
#define MASUmax 8
#define WHITE GOTE
#define BLACK SENTE
#define TAISENSUU 100

//���R�Ɏg���Ă����ϐ��B���[�v�ȂǁA���̏��ŏI�����̂Ɏg���̂𐄏��B
int i,j,k,l,m,n,o,p;
int x,y,z;
int BAN[MASUmax+2][MASUmax+2];//�����ɂ��̎��̔Ֆʂ������B
int hint[65];



//�������烁�C���v���O�����B
int J_BAN[MASUmax+2][MASUmax+2];
int J_flag[10];
int J_HINT[65];
int J_teban;
int J_TE;
int J_x,J_y;
int J_wincount[3]={0,0,0};

int henkan(int t){                               //�ϊ������֐�
	if(t/100==3){
		J_x=J_HINT[t%100]%10;
		J_y=J_HINT[(t%100)]/10;
	}else if(t/100==2){
		J_x=((t%100)-1)%8+1;
		J_y=((t%100)-1)/8+1;
	}else if(t/100==1){
		J_x=t%10;
		J_y=(t%100)/10;
	}
}

int AI(){
	return 301;                                   //AI�̈����B
}

int senshu(int shiaisuu){
	if(J_flag[4]==1){
		printf("�����ɂ������O���̐����������Ă�������");
		scanf("%d",&J_TE);
		henkan(J_TE);
	}else if(J_flag[4]==2){
		henkan(301);
	}else if(J_flag[4]==3){
		henkan(AI());
	}/*else if(J_flag[4]==4){
		���̂�������AI�̌Ăяo��������
		henkan(??);
	}*/
	
	if(J_BAN[J_x][J_y]!=HINT){
		J_turn(shiaisuu);
	}
}

int J_turn(int shiaisuu){
	for(i=0;i<=10;i++){
		for(j=0;j<=10;j++){
			BAN[i][j]=J_BAN[i][j];
		}
	}
	for(i=0;i<65;i++){                                     //�q���g�ƔՂ��^�������Ŏ���
		hint[i]=J_HINT[i];
	}
	if((J_teban==SENTE&&shiaisuu%2==1)||(J_teban==GOTE&&shiaisuu%2==0)){ //����������Ȃ�1P�������A�����Ȃ�1P�͌���
		J_flag[4]=J_flag[2];
	}else{
		J_flag[4]=J_flag[3];
	}
	senshu(shiaisuu);
}


int J_hyouzi(){                                //�\���v���O����
	int count[3];
	count[2]=count[1]=count[0]=0;
	printf("\n");
	for(j=0;j<=MASUmax;j++){
		if(j==0){
			printf(" ");
			for(k=1;k<=MASUmax;k++){
				printf("   %d",k);
			}
			printf("\n ����");
			for(o=1;o<=MASUmax-1;o++){
				printf("����");
			}
			printf("��\n");
		}else{
			for(i=0;i<=MASUmax;i++){
				if(i==0){
					printf("%d",j);
				}else if(J_BAN[i][j]==WHITE){
					printf("��");
					count[1]++;
				}else if(J_BAN[i][j]==BLACK){
					printf("��");
					count[2]++;
				}else if(J_BAN[i][j]==HINT){
					printf("��");
					count[0]++;
				}else if(J_BAN[i][j]==NONE){
					printf("  ");
				}
				printf("��");
			}
			if(j!=MASUmax){
				printf("\n ����");
				for(o=1;o<=MASUmax-1;o++){
					printf("����");
				}
				printf("��\n");
			}
		}
	}
	printf("\n ����");
	for(o=1;o<=MASUmax-1;o++){
		printf("����");
	}
	printf("��\n");
	printf("��%d�� ��%d��\n",count[1],count[2]);
}

int J_zyunbi(){                                  //�������������ʒu�ɋ����u��
	for(y=0;y<MASUmax+2;y++){
		for(x=0;x<MASUmax+2;x++){
			J_BAN[x][y]=NONE;
		}
	}
	J_BAN[4][5]=J_BAN[5][4]=SENTE;
	J_BAN[4][4]=J_BAN[5][5]=GOTE;
	J_teban=SENTE;
}

int J_passJud(int shiaisuu){                      //�p�X����������
	for(i=0;i<=64;i++){
		J_HINT[i]=0;
	}
	o=0;
	for(y=0;y<MASUmax+2;y++){
		for(x=0;x<MASUmax+2;x++){
			if(J_BAN[x][y]==HINT){                 //�q���g������
				J_BAN[x][y]=NONE;
			}
			J_KANAME(1);                            //���̏��ŁA���̈ʒu���u���邩�ǂ����𔻒肷��
		}
	}
	if(J_HINT[1]==0){                               //�q���g���ЂƂ��Ȃ����΁A�����͒u�����Ƃ��낪�Ȃ��Ƃ�������
		J_flag[0]++;
		J_teban*=-1;
		if(J_flag[0]==2){
			J_endflag(shiaisuu);                     //���񓯂����ۂ������΁A���ґłƂ��낪�Ȃ��̂ŁA�I�������B
		}else{
			J_passJud(shiaisuu);                     //�����ڂȂ��A���Ԃ������Ɉڂ��A�p�X�����B
		}
	}else{
		J_flag[0]=0;
	}

}

int J_hikkurikaeshi(){
	x=J_x;
	y=J_y;
	J_KANAME(2);                                     //KANAME��x��y���g�����̂ŁA�����ŕϊ�
}


int J_KANAME(int PorH){
	if((J_BAN[x][y]==NONE||J_BAN[x][y]==HINT)&&x>=1&&x<=8&&y>=1&&y<=8){//��Ȃ�&�Տ��ł̂ݔ����B
		for(i=-1;i<=1;i++){
			for(j=-1;j<=1;j++){                                        //���̃}�X�̎��蔪�}�X�𔻒�
				if(!(i==0&&j==0)){
					p=1;
					while(J_BAN[x+p*i][y+p*j]==-J_teban){
						p++;                                           //���̃}�X���瑊���̋�������肻�̕����ɐi��
					}
					if(J_teban==J_BAN[x+p*i][y+p*j]&&p!=1){            //�����̋��ł͂Ȃ��Ȃ����Ƃ��A�����̋��Ȃ��A
						if(PorH==1){
							J_BAN[x][y]=HINT;                          //���̏ꏊ���������Ƃ������������A
							J_HINT[++o]=(x)+(y)*10;                    //���̏ꏊ���L���B
						}else if(PorH==2){
							for(m=0;m<=p;m++){
								J_BAN[x+m*i][y+m*j]=J_teban;           //�u�����}�X���玩���̃}�X�܂ł̓G�̋����Ђ������Ԃ��B
							}
						}
					}
				}
			}
		}
	}
}

int J_shiaimae(){
	printf("�Ղ��g���Ȃ�1�A�g���Ȃ��Ȃ�0�����́F");
	scanf("%d",&J_flag[1]);
	printf("1P��");
	scanf("%d",&J_flag[2]);
	printf("2P��");
	scanf("%d",&J_flag[3]);
}

int J_endflag(int shiaisuu){
	int count[2]={0,0};
	for(i=1;i<=MASUmax;i++){                                            //���҂̃R�}�̐��𐔂��ďI�����邩�ǂ������肷��
		for(j=1;j<=MASUmax;j++){
			if(J_BAN[i][j]==SENTE){
				count[0]++;
			}else if(J_BAN[i][j]==GOTE){
				count[1]++;
			}
		}
	}
	if(count[0]==0||count[1]==0||count[0]+count[1]==MASUmax*MASUmax){   //�Е��̃R�}����0���A�����̃R�}���̍��v���}�X�̐��A�܂��S�����܂��Ă����ΏI��
		J_flag[0]=2;                                                    //�I���t���O
		if(count[0]!=count[1]){
			if(shiaisuu%2==1){                                          //����������Ȃ��A����1P
				count[0]>count[1]?J_wincount[0]++:J_wincount[1]++;      //�R�}����������������
				J_wincount[2]+=(count[0]-count[1]);                     //�R�}���̍��������A�ŏI�̃R�}�����������������̌v�Z���g��
			}else{                                                      //�����Ȃ甒��1P
				count[0]<count[1]?J_wincount[0]++:J_wincount[1]++;
				J_wincount[2]+=(count[1]-count[0]);
			}
		}
	}
}

int J_kekkahyouzi(){
	printf("1P:%d�� 2P:%d��\n",J_wincount[0],J_wincount[1]);
	if(J_wincount[0]!=J_wincount[1]){
		J_wincount[0]>J_wincount[1]?printf("1P�̏���"):printf("2P�̏���\n"); //�������������ق�������
	}else if(J_wincount[2]!=0){
		J_wincount[2]>0?printf("1P�̏���"):printf("2P�̏���\n");             //�������������Ȃ��A���������̍��v�������ق�������
	}else{
		printf("��������");                                                  //���̐��̍��v�������Ȃ��A��������
	}
}

int main(){
	int shiaisuu=0;
	int star[3]={0,0,0};
	J_shiaimae();
	while(shiaisuu++<TAISENSUU){                                              //TAISENSUU�̐������J���Ԃ�
		J_flag[0]=0;
		J_zyunbi();
		J_passJud(shiaisuu);
		do{
			if(J_flag[1]==1){
				J_hyouzi();
			}
			J_turn(shiaisuu);
			J_hikkurikaeshi();
			J_teban*=-1;
			J_endflag(shiaisuu);
			if(J_flag[0]!=2){
				J_passJud(shiaisuu);
			}
		}while(J_flag[0]!=2);
		if(J_flag[1]==1){
			J_hyouzi();
		}
	}
	J_kekkahyouzi();
	return 0;
}
