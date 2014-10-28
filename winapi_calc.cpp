#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK buttonclick(HWND hDlg,char a);
void CALLBACK calculation(HWND hDlg);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Calc");
HWND hEdit;
#define jum 106
#define CE 99
#define C 98
#define B 97
#define plus 101
#define minus 102
#define xx 103
#define nn 104
#define equal 105
double len=0;
int finder=0;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	//윈도우 클래스에 각각의 변수 저장

	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,340,230,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
char num[18]={'0'};
double result = 0;
int i=0;
char *resultEdit;
char tag=0;
int dec,sign;
char consider;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	char button;
	int temp;

	switch(iMessage) {
	case WM_CREATE:
		hEdit=CreateWindow(TEXT("edit"),NULL,WS_CHILD | WS_VISIBLE | WS_BORDER|ES_RIGHT|ES_READONLY,20,15,290,20,hWnd,(HMENU)100,g_hInst,NULL);
		SetDlgItemText(hWnd,100,TEXT("0"));
		CreateWindow("button","7",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20,50,50,25,hWnd,(HMENU)7,g_hInst,NULL);
		CreateWindow("button","8",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			80,50,50,25,hWnd,(HMENU)8,g_hInst,NULL);
		CreateWindow("button","9",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			140,50,50,25,hWnd,(HMENU)9,g_hInst,NULL);
		CreateWindow("button","4",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20,80,50,25,hWnd,(HMENU)4,g_hInst,NULL);
		CreateWindow("button","5",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			80,80,50,25,hWnd,(HMENU)5,g_hInst,NULL);
		CreateWindow("button","6",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			140,80,50,25,hWnd,(HMENU)6,g_hInst,NULL);
		CreateWindow("button","1",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20,110,50,25,hWnd,(HMENU)1,g_hInst,NULL);
		CreateWindow("button","2",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			80,110,50,25,hWnd,(HMENU)2,g_hInst,NULL);
		CreateWindow("button","3",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			140,110,50,25,hWnd,(HMENU)3,g_hInst,NULL);
		CreateWindow("button","0",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20,140,110,25,hWnd,(HMENU)0,g_hInst,NULL);
		CreateWindow("button",".",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			140,140,50,25,hWnd,(HMENU)jum,g_hInst,NULL);
		CreateWindow("button","Back",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			260,50,50,25,hWnd,(HMENU)B,g_hInst,NULL);
		CreateWindow("button","+",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			200,50,50,25,hWnd,(HMENU)plus,g_hInst,NULL);
		CreateWindow("button","-",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			200,80,50,25,hWnd,(HMENU)minus,g_hInst,NULL);
		CreateWindow("button","*",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			200,110,50,25,hWnd,(HMENU)xx,g_hInst,NULL);
		CreateWindow("button","/",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			260,140,50,25,hWnd,(HMENU)nn,g_hInst,NULL);
		CreateWindow("button","=",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			200,140,50,25,hWnd,(HMENU)equal,g_hInst,NULL);
		CreateWindow("button","C",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			260,80,50,25,hWnd,(HMENU)C,g_hInst,NULL);
		CreateWindow("button","CE",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			260,110,50,25,hWnd,(HMENU)CE,g_hInst,NULL);

		return 0;

	case WM_CHAR:

		if(LOWORD(wParam)>='0'&&LOWORD(wParam)<='9')
		{
			SetFocus(hWnd);
			buttonclick(hWnd,char(wParam));

		}
		else if(LOWORD(wParam)=='.')
		{
			buttonclick(hWnd,char(wParam));
		}
		else if(LOWORD(wParam)>=42&&LOWORD(wParam)<=47&&LOWORD(wParam)!=44&&LOWORD(wParam)!=46)
		{
			switch(LOWORD(wParam))
			{
			case 42:
				if(finder!=0)
				{
					SetFocus(hWnd);
					return 0;
				}
				result*=atof(num); 
				consider=3;
				calculation(hWnd);
				break;

			case 43:
				if(finder!=0)
				{
					SetFocus(hWnd);
					return 0;
				}
				result+=atof(num);
				consider=1;
				calculation(hWnd);
				break;
			case 45:
				if(finder!=0)
				{
					SetFocus(hWnd);
					return 0;
				}
				result-=atof(num);
				consider=2;
				calculation(hWnd);
				break;
			case 47:
				if(finder!=0)
				{
					SetFocus(hWnd);
					return 0;
				}
				result/=atof(num);
				consider=4;
				calculation(hWnd);
				break;
			}
		}
		else if(LOWORD(wParam)==VK_RETURN)
		{
			if(finder!=0)
			{
				SetFocus(hWnd);
				return 0;
			}
			switch(consider)
			{
			case 1: result+=atof(num); break;
			case 2: result-=atof(num); break;
			case 3: result*=atof(num); break;
			case 4: result/=atof(num); break;
			}
			calculation(hWnd);

			consider=0;


			if(result-(int)result==0)//입력받은 정수일 경우에는 뒤에 0 을 없애주는 함수
			{
				for(temp=dec+1;temp<=strlen(resultEdit);temp++)
				{
					if(resultEdit[temp]=='0')
					{
						len++;
					}
					if(len>=(strlen(resultEdit))/2-1)
					{
						resultEdit[dec+1]=0;
					}
				}
				len=0;
			}
			if(resultEdit[0]=='.')
			{
				for(temp=16;temp>=-1;temp--)
				{
					if(temp==-1)
					{
						resultEdit[temp+1]='0';
					}
					else {
						resultEdit[temp+1]=resultEdit[temp];
					}

				}

			}
			SetDlgItemText(hWnd,100,resultEdit);

			tag=2;
			i=0;
			SetFocus(hWnd);
			return 0;
		}
		else if(LOWORD(wParam)==VK_BACK)
		{
			i--;
			num[i]=0;
			SetDlgItemText(hWnd,100,num);
			return 0;
		}

		else{
			MessageBox(hWnd,TEXT("문자는 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);

		}



		return 0;


	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case 0:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='0';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 1:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='1';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 2:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='2';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 3:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='3';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 4:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='4';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 5:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='5';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 6:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='6';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 7:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='7';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 8:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='8';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case 9:
			if(i==17)
			{
				MessageBox(hWnd,TEXT("더이상 입력하실수 없습니다"),NULL,MB_OK|MB_ICONSTOP);
				return 0;
			}
			button='9';
			buttonclick(hWnd,button);
			SetFocus(hWnd);
			return 0;
		case plus:
			if(finder!=0)
			{
				SetFocus(hWnd);
				return 0;
			}
			if(tag!=0) result+=atof(num);
			consider=1;
			finder=1;
			calculation(hWnd);
			SetFocus(hWnd);
			return 0;

		case minus:
			if(finder!=0)
			{
				SetFocus(hWnd);
				return 0;
			}
			if(tag!=0) result-=atof(num);
			consider=2;
			finder=1;
			calculation(hWnd);
			SetFocus(hWnd);
			return 0;

		case xx:
			if(finder!=0)
			{
				SetFocus(hWnd);
				return 0;
			}
			if(tag!=0) result*=atof(num);
			consider=3;
			finder=1;
			calculation(hWnd);
			SetFocus(hWnd);
			return 0;

		case nn:
			if(finder!=0)
			{
				SetFocus(hWnd);
				return 0;
			}
			if(tag!=0) result/=atof(num);
			consider=4;
			finder=1;
			calculation(hWnd);
			SetFocus(hWnd);
			return 0;

		case jum:
			for(temp=0;temp<18;temp++)
			{
				if(num[temp]=='.')
				{
					MessageBox(hWnd,TEXT("소수점은 한번만 사용하실수 잇습니다."),NULL,MB_OK|MB_ICONSTOP);
					SetFocus(hWnd);
					return 0;
				}
			}
			if(num[0]=='0')
			{
				num[i]='0';
				num[i+1]='.';
				SetDlgItemText(hWnd,100,num);
				i+=2;
			}
			else {
				num[i]='.';
				SetDlgItemText(hWnd,100,num);
				i++;
			}
			SetFocus(hWnd);
			return 0;

		case equal:
			if(finder!=0)
			{
				SetFocus(hWnd);
				return 0;
			}
			switch(consider)
			{
			case 1: result+=atof(num); break;
			case 2: result-=atof(num); break;
			case 3: result*=atof(num); break;
			case 4: result/=atof(num); break;
			}
			calculation(hWnd);

			consider=0;


			if(result-(int)result==0)//입력받은 정수일 경우에는 뒤에 0 을 없애주는 함수
			{
				for(temp=dec+1;temp<=strlen(resultEdit);temp++)
				{
					if(resultEdit[temp]=='0')
					{
						len++;
					}
					if(len>=(strlen(resultEdit))/2-1)
					{
						resultEdit[dec+1]=0;
					}
				}
				len=0;
			}
			if(resultEdit[0]=='.')
			{
				for(temp=16;temp>=-1;temp--)
				{
					if(temp==-1)
					{
						resultEdit[temp+1]='0';
					}
					else {
						resultEdit[temp+1]=resultEdit[temp];
					}

				}

			}
			SetDlgItemText(hWnd,100,resultEdit);
			finder=1;
			tag=2;
			i=0;
			SetFocus(hWnd);
			return 0;

		case B:
			if(i!=0)
			{
				i--;
			}
			num[i]=0;
			SetDlgItemText(hWnd,100,num);
			SetFocus(hWnd);
			return 0;

		case CE:
			SetDlgItemText(hWnd,100,TEXT("0"));
			for(temp=0;temp<18;temp++)
			{
				num[temp]=0;
			}

			i=0;
			SetFocus(hWnd);
			return 0;

		case C:
			SetDlgItemText(hWnd,100,TEXT("0"));
			if(tag==0)
			{
				for(temp=0;temp<18;temp++)
				{
					num[temp]=0;
				}
				i=0;
				SetFocus(hWnd);
				return 0;
			}
			for(temp=0;temp<18;temp++)
			{
				num[temp]=0;
			}
			for(temp=0;temp<18;temp++)
			{
				resultEdit[temp]=0;
			}
			tag=0;
			i=0;
			result=0;
			SetFocus(hWnd);
			return 0;
		}
		SetFocus(hWnd);
		return 0;

	case WM_DESTROY:
		for(temp=0;temp<18;temp++)
		{
			num[temp]=0;
		}
		for(temp=0;temp<18;temp++)
		{
			resultEdit[temp]=0;
		}
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void CALLBACK buttonclick(HWND hDlg,char a)
{
	if(a=='0')
	{
		if(num[0]=='0'&&num[1]!='.')
		{
			return ;
		}
	}
	finder=0;
	num[i]=a;
	SetDlgItemText(hDlg,100,num);
	i++;
}
void CALLBACK calculation(HWND hDlg)
{
	int temp;
	int len=0;

	for(temp=0;temp<18;temp++)
	{
		if(num[temp]=='.') break;
		else if(num[temp]==0)
		{
			num[temp]='.';
			break;
		}
	}
	if(tag==0)
	{
		result=atof(num);
		for(temp=0;temp<18;temp++)
		{
			num[temp]=0;
		}

		tag++;
		i=0;
	}

	else{

		resultEdit=fcvt(result,strlen(num)/2,&dec,&sign);
		if(sign==0)
		{
			for(i=strlen(resultEdit);i>=dec;i--)
			{
				resultEdit[i+1]=resultEdit[i];
				if(i==dec)
				{
					resultEdit[i]='.';
				}
			}
		}
		else if(sign==1)
		{
			for(i=strlen(resultEdit);i>=0;i--)
			{
				resultEdit[i+1]=resultEdit[i];
				if(i==0)
				{
					resultEdit[i]='-';
				}
			}
			for(i=strlen(resultEdit);i>=dec+1;i--)
			{

				resultEdit[i+1]=resultEdit[i];
				if(i==dec+1)
				{
					resultEdit[i]='.';
				}
			}
		}
		if(result-(int)result==0)//입력받은 정수일 경우에는 뒤에 0 을 없애주는 함수
		{
			resultEdit[dec+1]=0;
		}
		SetDlgItemText(hDlg,100,resultEdit);
		for(temp=0;temp<18;temp++)
		{
			num[temp]=0;
		}
		i = 0;
	}
	finder=1;

}