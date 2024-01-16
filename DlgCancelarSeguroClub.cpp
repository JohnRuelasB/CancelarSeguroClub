// DlgCancelarSeguroClub.cpp: archivo de implementación
//

#include "stdafx.h"
#include "CancelarSeguroClub.h"
#include "DlgCancelarSeguroClub.h"

#include "sysCancelarSeguroClub.hpp"
#include "gnwproto.hpp"
#include "cnwproto.hpp"
#include "movtos.hpp"
#include "password.hpp"
#include "wtienda.hpp"
#include "process.h"
#include "folios.hpp"

#include "CCrHuellas.hpp"
#include "CCdFechaGnDominio.hpp"
#include "CObtenerNombreCliente.hpp"
#include "CVerificarCliente.hpp"
#include "CConsultarPID.hpp"
#include "CInsertarTmpCaCarmov1.hpp"
#include "CStatusFolioCrSeguros.hpp"
#include "CStatusFolioCrSeguros02.hpp"
#include "CInsertarTmpCaSegCteNvo.hpp"
#include "CConsultarCteCrHuellas.hpp"
#include "CNOMBRESEXFECCRCLIENTE.HPP"
#include "CConsultarCliente.hpp"
#include "CInsTemCaCarmovAdics.hpp"
#include ".\dlgcancelarseguroclub.h"
#include "CargarDll.h"
#include "CMaximo.hpp"
#include "CConsultarMensajeSeguro.hpp"

#include "strsafe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void mem_cpy(void *dest, void *src, size_t n){
	    char *csrc = (char*)src;
        char *cdest = (char*)dest;
        for(unsigned int i=0; i<n; i++)
                cdest[i] = csrc[i];
}

class CAboutDlg : public CDialogoML
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogoML(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogoML::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogoML)
END_MESSAGE_MAP()


// Cuadro de diálogo de CDlgCancelarSeguroClub



CDlgCancelarSeguroClub::CDlgCancelarSeguroClub(CWnd* pParent /*=NULL*/)
	: CDialogoML(CDlgCancelarSeguroClub::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgCancelarSeguroClub::DoDataExchange(CDataExchange* pDX)
{
	CDialogoML::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAUSA, m_causa);
	DDX_Control(pDX, IDC_CLIENTE, m_cliente);
	DDX_Control(pDX, IDC_FOLIO, m_folio);
	DDX_Control(pDX, IDC_NOMBRECLIENTE, m_nombreCliente);
	DDX_Control(pDX, IDC_ESCSALIR, m_escSalir);
	DDX_Control(pDX, IDC_F10ACEPTAR, m_f10Aceptar);
	DDX_Control(pDX, IDC_TIPO, m_tipo);
	DDX_Control(pDX, IDC_TIPOSEGURO, m_tiposeguro);
}

BEGIN_MESSAGE_MAP(CDlgCancelarSeguroClub, CDialogoML)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ESCSALIR, OnBnClickedEscsalir)
	ON_BN_CLICKED(IDC_F10ACEPTAR, OnBnClickedF10aceptar)
	ON_EN_SETFOCUS(IDC_CAUSA, OnEnSetfocusCausa)
	ON_EN_SETFOCUS(IDC_CLIENTE, OnEnSetfocusCliente)
	ON_EN_SETFOCUS(IDC_FOLIO, OnEnSetfocusFolio)
	ON_EN_SETFOCUS(IDC_NOMBRECLIENTE, OnEnSetfocusNombrecliente)
	ON_EN_CHANGE(IDC_TIPO, OnEnChangeTipo)
END_MESSAGE_MAP()


// Controladores de mensaje de CDlgCancelarSeguroClub

BOOL CDlgCancelarSeguroClub::OnInitDialog()
{

	HRESULT hr = 0;
bool bContinua=true, bContinuar=false;
char cNombre[20], cApellidoPaterno[20], cApellidoMaterno[20], cSqlTxt[255];
int iEstaCte=0, iFlag=0;
CString sTexto;
char cMensajeOut[MAX_BUFFER_XML] = {0};

	CDialogoML::OnInitDialog();

	
		/*agregarControl ( IDD_DLGCANCELARSEGUROCLUB, this, CTRL_DIALOGO );

		agregarControl ( IDC_TIPO                );
		agregarControl ( IDC_TIPOSEGURO          );
		agregarControl ( IDC_STATIC_CUADRO_CAUSA );
		agregarControl ( IDC_STATIC_NO_PAGAR     );
		agregarControl ( IDC_STATIC_MAL_SERVICIO );
		agregarControl ( IDC_STATIC_CLIENTE_SOL  );
		agregarControl ( IDC_STATIC_OTRO         );
		agregarControl ( IDC_STATIC_CAUSA        );
		agregarControl ( IDC_STATIC_CUADRO_ASEG  );
		agregarControl ( IDC_STATIC_CLIENTE_DOS  );
		agregarControl ( IDC_STATIC_FOLIO        );
		agregarControl ( IDC_STATIC_NOMBRE       );*/


		if( obtenerCdFechaCoppel() )
		{
			if( iSistema == 4 )
			{
				iFlag=checarHuellaCliente(lCliente,iCaja,lEmpleado,iMuestraMsg,iTienda);																														    
			}
			else
			{
				iFlag=1;
			}

			if ( iFlag > 0 )




			{		
				
		        		
				// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
				//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
				SetIcon(m_hIcon, TRUE);			// Establecer icono grande
				SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

				if( iTipo == 1 )
				{
					SetWindowText( "CANCELACION DEL SEGURO CLUB PROTECCION FAMILIAR" );//CANCELACION DEL SEGURO CLUB PROTECCION COPPEL
				}
				else
				{
					SetWindowText( "CANCELACION DEL SEGURO CLUB CONYUGAL" );//CANCELACION DEL SEGURO CLUB CONYUGAL
				}

				ShowWindow( SW_SHOWMAXIMIZED );
				
				crearMensaje( this, m_barraMsj, m_textoMsj );
				ponerMensaje( this, m_barraMsj, m_textoMsj, "[ ESC ] Cancelar     [ F10 ] Aceptar");//[ ESC ] Cancelar     [ F10 ] Aceptar

				iControles = 1;
				iFoco = 0;
				iAllOk = 0;
				asignarFoco();
			    
				m_causa.SetWindowText( "" );
				m_causa.SetLimitText( 1 );	    

				{		
					CObtenerNombreCliente consulta( &odbcCartera ); //conexión a cartera
					
					bContinuar = ObtenerNombreCliente( lCliente, cNombre, cApellidoPaterno, cApellidoMaterno, consulta.odbc, cSqlTxt, iEstaCte );

					if( bContinuar )
					{
						if( iEstaCte == 1 )
						{
							sTexto.Format( "%ld", lCliente );
							m_cliente.SetWindowText( sTexto );

							sTexto.Format( "%ld", lFolio );
							m_folio.SetWindowText( sTexto );

							sTexto.Format( "%s %s %s", cNombre, cApellidoPaterno, cApellidoMaterno );
							m_nombreCliente.SetWindowText( sTexto );
							if (iTipo == 2)
							{
								//Mira vjo..tengo un control
								m_tiposeguro.SetWindowText("Tipo");
								sTexto.Format( "%d", 2 );
								m_tipo.SetWindowText( sTexto );							
							}
						}
						else
						{
							
							sTexto.Format( "Cliente número: %ld no está registrado", lCliente );//Cliente número: %ld no está registrado
							AfxMessageBox( sTexto );
							OnBnClickedEscsalir();		
						}
					}
					else
					{
						//Se obtiene el error
						sServer.Trim();
						/*
						to do
						//TO DO sprintf(cIPDestino,"%s",sServer);
						*/
						hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
						

						cIPDestino[15] = 0;

						grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "OnInitDialog", cSqlTxt,lEmpleado,"Error #6220",consulta.odbc,iMuestraMsg);
						OnBnClickedEscsalir();
					}
				}
			}
			else
			{
				OnBnClickedEscsalir();				
			}
		}
		else
		{
			OnBnClickedEscsalir();				
		}
	
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CDlgCancelarSeguroClub::OnSysCommand(UINT nID, LPARAM lParam)
{
	/*if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else*/
	{
		CDialogoML::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CDlgCancelarSeguroClub::OnPaint() 
{
	/*if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else*/
	{
		CDialogoML::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CDlgCancelarSeguroClub::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDlgCancelarSeguroClub::asignarFoco()
{	
    switch (iFoco)
    {
		case 0:
            m_causa.SetFocus();
            break;
		case 1:
		//	m_escSalir.SetFocus();
		//	break;
		//case 2:
		//	m_f10Aceptar.SetFocus();
  //          break;
		//case 3:
			iFoco = 0;
            m_causa.SetFocus();
			break;
	}
}

bool CDlgCancelarSeguroClub::validarControl(char *cCadena)
{
    bool bValorRegresa = true;
    CString sTexto;
	char cMensajeOut[MAX_BUFFER_XML] = {0};
	
	ZeroMemory( cCadena, size_t(cCadena));

    switch( iFoco )
    {
        case 0 :
			m_causa.GetWindowText( sTexto );			
			sTexto.TrimLeft();
			sTexto.TrimRight();
			iCausa = strtol( sTexto,NULL,10 );

			if( iCausa <= 0 || iCausa > 4 )
			{
				mem_cpy( cCadena, "Causa de cancelación inválida" , 29 );//Causa de cancelación inválida
				cCadena[ 29 ] = 0;
				bValorRegresa = false;
			}
			break;

		default:
            break;
    }
    return bValorRegresa;
}


void CDlgCancelarSeguroClub::OnBnClickedEscsalir()
{
	CDialogoML::OnOK();
}

void CDlgCancelarSeguroClub::OnBnClickedF10aceptar()
{
	bool bConsulta = true, bEstaCteCrHuellas = false, bContinuar = true;		
	char cStatusSeguro = ' ', cSqlTxt[255] = {0};
	int iSegCnseg = 0, iResp = 0, iSegCartera = 0, iSegCancelado = 0, iModulo = 0;
	CString sTexto, sSqlTxt, sEjecutar;
	int iFlagTieneAdicionales = 0;
	long lGteHuella = 0L;
	char cMensajeOut[MAX_BUFFER_XML] = {0};

	if( validarControles() )
	{
        if( iSistema == SISTEMA_CLIENTES_NUEVOS )
        {
			bConsulta = buscaSeguroCnsegCarmov( 1, lCliente, iSegCnseg );
        }
        if( iSistema == SISTEMA_CAJAS )
        {			
            bConsulta = buscaSeguroCnsegCarmov( 2, lCliente, iSegCnseg );
        }
        if( iSegCnseg == 0 && bConsulta == TRUE )
        {
			bConsulta = buscaSeguroCartera( lCliente, iSegCartera, iSegCancelado, cStatusSeguro, iFlagTieneAdicionales );
        }
		else if( bConsulta == TRUE )
		{
			if( iSistema == SISTEMA_CLIENTES_NUEVOS )
            {
				AfxMessageBox( "PARA CANCELAR SEGUROS DE ESTE DIA PASE A LA OPCION F6 CONSULTA/CANCELACION DE RECIBOS DE SEGUROS", MB_ICONINFORMATION );//PARA CANCELAR SEGUROS DE ESTE DIA PASE A LA OPCION \n F6 CONSULTA/CANCELACION DE RECIBOS DE SEGUROS
            }
            else
            {
				AfxMessageBox( "PARA CANCELAR SEGUROS DE ESTE DIA PASE A LA OPCION CONSULTA/CANCELACION DE RECIBOS DE CAJAS", MB_ICONINFORMATION );//PARA CANCELAR SEGUROS DE ESTE DIA PASE A LA OPCION \n CONSULTA/CANCELACION DE RECIBOS DE CAJAS
            }			
        }
		if( bConsulta == TRUE )
		{
			if( iSegCartera == 1 )
			{
				if( iSegCancelado == 0 )
				{
					graboSeguros( lCliente, iCausa, lFolio );
				}
				else
				{
					AfxMessageBox( "El seguro ya está cancelado", MB_ICONINFORMATION );//El seguro ya está cancelado
				}
			}			
		}
		OnBnClickedEscsalir();
	}
}

/*int  CDlgCancelarSeguroClub::crearArchivoHuellas()
{
	CString sConsulta;
	int iRespuesta = 1 ;
	char cRespuesta[150], cRespuesta2[80];
	long lHuella= 0L;
	Templ Templates, templ;
	

	CCrHuellas consultarcrHuella( &odbc_3 ); // bd huella cliente

	sConsulta.Format(" SELECT cliente, flagadicional, templatededoderecho001, templatededoderecho002, templatededoderecho003, templatededoderecho004, templatededoderecho005, templatededoderecho006, templatededoderecho007, templatededoderecho008, templatededoderecho009, templatededoderecho010, templatededoderecho011, templatededoderecho012, templatededoderecho013, templatededoderecho014, templatededoderecho015, templatededoderecho016, templatededoderecho017, templatededoderecho018, templatededoderecho019, templatededoderecho020,"
					" templatededoderecho021, templatededoderecho022, templatededoderecho023, templatededoderecho024, templatededoderecho025, templatededoderecho026, templatededoderecho027, templatededoderecho028, templatededoderecho029, templatededoderecho030, templatededoderecho031, templatededoderecho032, templatededoderecho033, templatededoderecho034, templatededoderecho035, templatededoderecho036, templatededoderecho037, templatededoderecho038, templatededoderecho039, templatededoderecho040, templatededoderecho041, templatededoderecho042, templatededoderecho043,"
					" templatededoderecho044, templatededoderecho045, templatededoderecho046, templatededoderecho047, templatededoderecho048, templatededoderecho049, templatededoderecho050, templatededoderecho051, templatededoderecho052, templatededoderecho053, templatededoderecho054, templatededoderecho055, templatededoderecho056, templatededoderecho057, templatededoderecho058, templatededoderecho059, templatededoderecho060, templatededoderecho061, templatededoderecho062, templatededoderecho063, templatededoderecho064, templatededoderecho065, templatededoderecho066,"
					" templatededoderecho067, templatededoderecho068, templatededoderecho069, templatededoderecho070, templatededoderecho071, templatededoderecho072, templatededoderecho073, templatededoderecho074, templatededoderecho075, templatededoderecho076, templatededoderecho077, templatededoderecho078, templatededoderecho079, templatededoderecho080, templatededoderecho081, templatededoderecho082, templatededoderecho083, templatededoderecho084, templatededoderecho085, templatededoderecho086, templatededoderecho087, templatededoderecho088"
					" FROM crhuellas WHERE cliente = %ld", lCliente );
    AfxMessageBox(sConsulta);
	if ( consultarcrHuella.Exec( sConsulta ) )
	{
		consultarcrHuella.activarCols();
		if ( consultarcrHuella.Leer() )
		{
			unlink( "c:\\template\\template.02" );			
			SecureZeroMemory(cRespuesta, ' ', sizeof(cRespuesta));
			memcpy( &Templates.templates1, &consultarcrHuella.templatededoderecho, 700 );

			SecureZeroMemory(cRespuesta2, 0, sizeof(cRespuesta2));
			for( int i = 0; i < 10; i++ )
			{
				cRespuesta2[i] = Templates.templates1[i]+'0';
			}
			lHuella = valorCampo( cRespuesta2, 9 );

			if ( lHuella == 999999999 )
			{
				//huella invalida
				//iFlag = 1;
				//iFlagInvalido = 1;
				iRespuesta = -1;
				AfxMessageBox(" CLIENTE CUENTA CON HUELLA INVALIDA ");
			}
			else
			{
				C_Archivo arc_templ;
				arc_templ.abrir( "c:\\template\\template.02", sizeof(Templates));
				SecureZeroMemory(&templ,0,sizeof(templ));

				if ( consultarcrHuella.cliente == lCliente )
				{
					memcpy( templ.templates1, &consultarcrHuella.templatededoderecho, 700 );
					arc_templ.grabar(&templ,0L);
					arc_templ.cerrar();
				}
			}
		}
		else
		{
			iRespuesta = -1;
			AfxMessageBox(" CLIENTE NO SE ENCONTRO EN LA CARTERA DE HUELLAS ");
		}
	}
    else
	{
		consultarcrHuella.odbc->GetLastError(consultarcrHuella.GetHstmt());
		//TO DO sprintf(cConsulta,"%s",sConsulta);
		cConsulta[ sConsulta.GetLength() ] = 0;
		//TO DO sprintf(cIPDestino,"%s",sServer);
		cIPDestino[15] = 0;
		grabarMensajeError( "N",iCaja,cIPDestino,"CancelarSeguroClub","CDlgCancelarSeguroClub","validarHuellaCliente",cConsulta,lEmpleado,"ERROR EN LA CONSULTA",consultarcrHuella.odbc,iMuestraMsg );
	}

	return iRespuesta;			
}*/


bool CDlgCancelarSeguroClub::validarControles()
{
	char cPaso[ 80 ];
	int i, iFocoAnt;
	bool bValorRegresa = false, bandera = true;	

	iFocoAnt = iFoco;

    for( i = 0; i < iControles; i++ )
    {
        iFoco = i;
        bandera = validarControl( cPaso );
        if( !bandera )
        {
            AfxMessageBox( cPaso );
			m_causa.SetWindowText( "" );
			iFoco = 0;
			asignarFoco();
            break;
        }
    }

    if ( bandera )
    {
		bValorRegresa = true;
    }

    iFoco = iFocoAnt;
	asignarFoco();

	return bValorRegresa;
}


void CDlgCancelarSeguroClub::OnEnSetfocusCausa()
{
	validarClick( 0 );
}

bool CDlgCancelarSeguroClub::validarClick(int nTmpFocus)
{
    CString msg;
	char cPaso[ 80 ];
    int nElementoTmp, i;
    bool regresa = true;

    if( iFoco < nTmpFocus )
    {
        // validar control anterior
        if( ! ( cPaso ) )
        {
            asignarFoco();
            if( iFoco != iControles )//numero de controles para los que se quieren se vea el mensaje de error
            {
                if( !ShiftTab )
                {
                    AfxMessageBox( cPaso );
                }
            }
            regresa = false;
        }
        else
        {
            nElementoTmp = iFoco;
            iFoco = nTmpFocus;
            for( i = 0; i <= nTmpFocus; i++ )
            {
                iFoco = i;
                //valida hacia abajo los controles
                if( !validarControl( cPaso ) )
                {
                    break;
                }
            }
            asignarFoco();
        }
    }
    else
    {
        iFoco = nTmpFocus;
    }
	return regresa;
}


BOOL CDlgCancelarSeguroClub::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    char cPaso[ 80 ];
	CString sTexto, sTexto2;
	short iRueda;
	char cMensajeOut[MAX_BUFFER_XML] = {0};
	
    ShiftTab = false;

	if( pMsg->message == WM_SYSKEYDOWN ) // Teclas virtuales 
	{  
		if ( pMsg->wParam== VK_F10 )
		{
			OnBnClickedF10aceptar();
			pMsg->wParam = NULL;
		}
		if( GetKeyState( VK_MENU ) & 0x8000 || pMsg->wParam == VK_F10 ) //ELIMINO  ALT  
				pMsg->wParam = VK_SHIFT;  
	}  
	if( pMsg->message == WM_MOUSEWHEEL )
	{
		iRueda = GET_WHEEL_DELTA_WPARAM( pMsg->wParam );
		if( iRueda != 0)   // iRueda > 0 Scroll se movio hacia adelante
		{					// iRueda < 0 Scroll se movio hacia atras
			pMsg->wParam = NULL;
		}
	}
	else
	{
		if( pMsg->message == WM_KEYDOWN )
		{
			if( pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP )
			{
				iFoco--;
				if( iFoco < 0 )	
					iFoco = 0;
				asignarFoco();
			}
			//if( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB || pMsg->wParam == VK_DOWN || pMsg->wParam == VK_RIGHT )
			if( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB || pMsg->wParam == VK_RIGHT )
			{
				//if( !boton() )
				{
					if( iFoco <= iControles ) //numero de controles
					{
						if( validarControl( cPaso ) )
						{
							iFoco++;
							asignarFoco();
						}
						else
						{
							if( !ShiftTab )
							{
								AfxMessageBox( cPaso );
								m_causa.SetWindowText( "" );
							}
						}
						return TRUE; 
					}
					else
					{
						if( pMsg->wParam != VK_RETURN )
						{
							iFoco++;
							asignarFoco();
						}
						else
						{
							asignarFoco();
						}
						return TRUE;
					}
				}
				//else
				//{
				//	if( pMsg->wParam == VK_RETURN )
				//	{
				//		switch( iFoco )
				//		{
				//			case 1:
				//				OnBnClickedEscsalir();
				//				break;
				//			case 2: 
				//				OnBnClickedF10aceptar();
				//				break;
				//			default:
				//				break;
				//		}
				//		return TRUE;
				//	}
				//	iFoco++;
				//	asignarFoco();
				//	return TRUE;
				//}
			}
			else
			{
				if( pMsg->wParam == VK_TAB && GetKeyState( VK_SHIFT ) & 0x8000 )
				{
					ShiftTab = true;
				}
				else
				{
					switch( pMsg->wParam )
					{
						case VK_F1:
							{
								AfxMessageBox( "No existe ayuda para este dato" );//No existe ayuda para este dato
							}
							break;
						case VK_F10:
							OnBnClickedF10aceptar();
							break;
						case VK_ESCAPE:
							OnBnClickedEscsalir();
							break;
						default:
							break;
					}
				}
			}
		}
	}

	return CDialogoML::PreTranslateMessage(pMsg);
}
//bool CDlgCancelarSeguroClub::boton()
//{
//    CWnd *pWnd = GetFocus();
//    bool valorRegresa = false;
//
//    switch( pWnd->GetDlgCtrlID() )
//    {
//		case IDC_ESCSALIR:
//			valorRegresa = true;
//			break;
//        case IDC_F10ACEPTAR:
//            valorRegresa = true;
//            break;
//		default:
//			break;
//    }
//    return valorRegresa;
//}

void CDlgCancelarSeguroClub::OnEnSetfocusCliente()
{
	asignarFoco();
}

void CDlgCancelarSeguroClub::OnEnSetfocusFolio()
{
	asignarFoco();
}

void CDlgCancelarSeguroClub::OnEnSetfocusNombrecliente()
{
	asignarFoco();
}

//bool CDlgCancelarSeguroClub::abrirConexionTienda(void)
//{
//	bool valorRegresa = false;
//    CString sPassword,sBd,sUsuario;
//	char cPassword[40], cUser[20], cDataBase[25];
//
//	//TO DO sprintf(cDataBase,"tienda.%04d",iTienda);
//	cDataBase[11] = 0;
//	//TO DO sprintf(cUser,"systienda%04d",iTienda);
//	cUser[13] = 0;
//	generarPasswordDB(cUser, cDataBase, cPassword);
//	cPassword[32] = 0;
//
//	sBd = cDataBase;
//	sUsuario = cUser;
//	sPassword = cPassword;
//
//    sServer.TrimLeft();sServer.TrimRight();
//    sUsuario.TrimLeft();sUsuario.TrimRight();
//    sPassword.TrimLeft();sPassword.TrimRight();
//    sBd.TrimLeft();sBd.TrimRight();
//
//    //Establecer conexión
//	if( odbc.Open("PostgreSQL",sServer,sUsuario,sPassword,sBd) == TRUE )
//	{
//		valorRegresa = true;
//	}
//
//	return valorRegresa;
//}

//bool CDlgCancelarSeguroClub::abrirConexionCartera(void)
//{
//	bool valorRegresa = false;
//    CString sPassword,sBd,sUsuario;
//	char cPassword[40], cUser[20], cDataBase[25];
//
//	//TO DO sprintf(cDataBase,"cartera");
//	cDataBase[7] = 0;
//	//TO DO sprintf(cUser,"systiendacartera");
//	cUser[16] = 0;
//	generarPasswordDB(cUser, cDataBase, cPassword);
//	cPassword[32] = 0;
//
//	sBd = cDataBase;
//	sUsuario = cUser;
//	sPassword = cPassword;
//
//    sServer.TrimLeft();sServer.TrimRight();
//    sUsuario.TrimLeft();sUsuario.TrimRight();
//    sPassword.TrimLeft();sPassword.TrimRight();
//    sBd.TrimLeft();sBd.TrimRight();
//
//    //Establecer conexión
//	if( odbc_1.Open("PostgreSQL",sServer,sUsuario,sPassword,sBd) == TRUE )
//	{
//		valorRegresa = true;
//	}
//
//	return valorRegresa;
//}

bool CDlgCancelarSeguroClub::obtenerCdFechaCoppel()
{

	HRESULT hr = 0;
	CString sSqlTxt;

	bool bConsulta = true;
	sSqlTxt.Format( "SELECT ciudad, fecha FROM gnDominio" );
	CCdFechaGnDominio xCdFechaCoppel( &odbcTiendaNumero );
	if( xCdFechaCoppel.Exec( sSqlTxt ) )
	{
		xCdFechaCoppel.activarCols();
		if( xCdFechaCoppel.Leer() )
		{
			iCiudad     = xCdFechaCoppel.ciudad;
			iAnioActual = xCdFechaCoppel.fecha.ano();
			iMesActual  = xCdFechaCoppel.fecha.mes();
			iDiaActual  = xCdFechaCoppel.fecha.dia();
			sFechaGn.Format("%04d%02d%02d", iAnioActual, iMesActual, iDiaActual);
		}
	}
	else
	{
		//Se obtiene el error
		sServer.TrimLeft();
		sServer.TrimRight();
		/*
		//TO DO sprintf(cIPDestino,"%s",sServer);
		*/
		hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
		
		cIPDestino[15] = 0;
		sSqlTxt.TrimLeft();
		sSqlTxt.TrimRight();
		/*
		//TO DO sprintf(cConsulta,"%s",sSqlTxt);
		*/
		hr = StringCchPrintf(cConsulta,size_t(cConsulta),TEXT("%s"),sSqlTxt);
		
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		xCdFechaCoppel.odbc->GetLastError(xCdFechaCoppel.GetHstmt());
		grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "obtenerCdFechaCoppel", cConsulta,lEmpleado,"Error #6223",xCdFechaCoppel.odbc,iMuestraMsg);
		bConsulta = false;
	}

	return bConsulta;
}

bool CDlgCancelarSeguroClub::buscaSeguroCnsegCarmov( int iTabla, long lCliente, int &iSegCnseg )
{

	HRESULT hr = 0;
	//iTabla = 1, Busca el seguro club en caSegurosClientesNuevos
	//iTabla = 2, Busca el seguro club en caCarmov

	CString sSqlTxt;
	 
	bool bConsulta = true;
	iSegCnseg = 0;

	obtenerCdFechaCoppel();    

	if( iTabla == 1 ) 
	{
		if ( iTipo == 1 )
		{	
			sSqlTxt.Format( "SELECT cliente FROM caSegurosClientesNuevos "
				            "WHERE clave = 'G' AND tipomovimiento = '6' AND cliente = %ld and fechaventa = '%s' and bonificacion=0", lCliente,sFechaGn); //cve vta seguros club
		}
		else
		{	
			sSqlTxt.Format( "SELECT cliente FROM caSegurosClientesNuevos "
				            "WHERE clave = 'G' AND tipomovimiento = '6' AND cliente = %ld and fechaventa = '%s' and bonificacion=77", lCliente,sFechaGn); //cve vta seguros club
		}
	}
	else if( iTabla == 2 )
	{
		if ( iTipo == 1 )
		{
			sSqlTxt.Format( "SELECT cliente FROM caCarmov "
				            "WHERE clave = 'G' AND tipomovimiento = '6' AND cliente = %ld and fecha='%s' and bonificacion=0", lCliente ,sFechaGn);
		}
		else
		{
			sSqlTxt.Format( "SELECT cliente FROM caCarmov "
				            "WHERE clave = 'G' AND tipomovimiento = '6' AND cliente = %ld and fecha='%s' and bonificacion=77", lCliente ,sFechaGn);
		}
	}

	CVerificarCliente xbuscaSeguro( &odbcTiendaNumero ); //conexión a tienda.nnnn
	if( xbuscaSeguro.Exec( sSqlTxt ) )
	{
		xbuscaSeguro.activarCols();
		if( xbuscaSeguro.Leer() )
		{
			iSegCnseg = 1;
        }
    }
	else
	{
		//Se obtiene el error
		sServer.TrimLeft();
		sServer.TrimRight();
		/*
		to do
		//TO DO sprintf(cIPDestino,"%s",sServer);
		*/
		hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
		cIPDestino[15] = 0;
		sSqlTxt.TrimLeft();
		sSqlTxt.TrimRight();
		/*to do
		//TO DO sprintf(cConsulta,"%s",sSqlTxt);
		*/
		hr = StringCchPrintf(cConsulta,size_t(cConsulta),TEXT("%s"),sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		xbuscaSeguro.odbc->GetLastError(xbuscaSeguro.GetHstmt());
		grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "buscaSeguroCnseg", cConsulta,lEmpleado,"Error #6225",xbuscaSeguro.odbc,iMuestraMsg);
		bConsulta = false;
	}

	return bConsulta;
}

bool CDlgCancelarSeguroClub::buscaSeguroCartera( long lCliente, int &iSegCartera, int &iSegCancelado, char &cStatusSeguro, int &iFlagTieneAdicionales )
{
	HRESULT hr = 0;
	CString sSqlTxt, sFechaVenc, sTexto;
	bool bConsulta = true, bMostrarSeguro = false;
	long lFolioMenu = 0L, lFolioConsulta = 0L;

	iSegCartera = 0;
	iSegCancelado = 0;

	if ( iTipo == 1 )
	{		
		sSqlTxt.Format( "SELECT cliente, statusseguro, folio, claveconyugal, fechavencimiento FROM crSeguros "
			            "WHERE claveseguro = 'C' AND cliente = %ld AND claveconyugal in (0,1) and tiposeguro in (0,1) order by fechavencimiento", lCliente );
	}
	else
	{		
		sSqlTxt.Format( "SELECT cliente, statusseguro, folio, claveconyugal FROM crSeguros "
			            "WHERE claveseguro = 'C' AND cliente = %ld AND claveconyugal=1", lCliente );
	}

	CStatusFolioCrSeguros02 crSegurosSQL( &odbcCartera ); //conexión a cartera
	if( crSegurosSQL.Exec( sSqlTxt ) )
	{
		crSegurosSQL.activarCols();
		while( crSegurosSQL.Leer() && !bMostrarSeguro)
		{						
			iSegCartera = 1;
			//preguntar si el seguro esta cancelado
			cStatusSeguro = crSegurosSQL.statusseguro[0];
			if( cStatusSeguro == 'C' ) //cancelado
			{
				iSegCancelado = 1;
			}
			else
			{
				if(cStatusSeguro == 'V' || cStatusSeguro == 'A' || cStatusSeguro == 'P')
				{
					if (cStatusSeguro == 'A')
					{
						sFechaVenc.Format("%04d%02d%02d",crSegurosSQL.fechavencimiento.ano(),crSegurosSQL.fechavencimiento.mes(), crSegurosSQL.fechavencimiento.dia());

						if( strtol(sFechaVenc,NULL,10) < strtol(sFechaGn,NULL,10) )
						{
							bMostrarSeguro = true;
							lFolioConsulta  = crSegurosSQL.folio;
							if( crSegurosSQL.claveconyugal == 1 )
							{
								iFlagTieneAdicionales = 1;
							}
						}
						else
						{
							iSegCancelado = 1;
						}
					}
					else
					{
						iSegCancelado = 0;
						bMostrarSeguro = true;
						lFolioConsulta  = crSegurosSQL.folio;
					}
				}
			}
        }

		m_folio.GetWindowText (sTexto);
		sTexto.Trim ();
		lFolioMenu = strtol( sTexto,NULL, 10 );

		if (lFolioMenu == lFolioConsulta )
		{
			iSegCancelado = 0;
		}
		else
		{
			iSegCancelado = 1;
		}
    }
	else
	{
		//Se obtiene el error
		sServer.Trim();		
		/*
		to do
		//TO DO sprintf(cIPDestino,"%s",sServer);
		*/
		hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
		cIPDestino[15] = 0;
		sSqlTxt.TrimLeft();
		/*
		//TO DO sprintf(cConsulta,"%s",sSqlTxt);
		*/
		hr = StringCchPrintf(cConsulta,size_t(cConsulta),TEXT("%s"),sSqlTxt);
		
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		crSegurosSQL.odbc->GetLastError(crSegurosSQL.GetHstmt());
		grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "buscaSeguroCartera", cConsulta,lEmpleado,"Error #6226",crSegurosSQL.odbc,iMuestraMsg);
		bConsulta = false;
	}

	return bConsulta;
}

void CDlgCancelarSeguroClub::graboSeguros( long lCliente, int iCausaBaja, long lFolio )
{
	HRESULT hr = 0;
	bool bContinuar = true;
	int iSeguroCartera = 0, iEncontro = 0, iSeguroCancelado = 0, iPID = 0, iPasaTmp = 0;
	char cNombreTablaOrigen[50]={0}, cStatusSeg/*cFolio[5]*/;
	CString sSqlTxt;
	int iFlagTieneAdicionales = 0;
	char cMensajeOut[MAX_BUFFER_XML] = {0};

	bContinuar = buscaSeguroCartera( lCliente, iSeguroCartera, iSeguroCancelado, cStatusSeg, iFlagTieneAdicionales );
	
	if( bContinuar )
	{
	    if( iSeguroCartera )     //si es seguro club de proteccion
        {   
			if(cStatusSeg=='P')
			{
				fObtenerMensajeSeguro();
			}
			else
			{
				if( iSistema == SISTEMA_CAJAS ) //if( iFlag == 1 )
				{
					//Crear tmp de aCarmov
					/*
					TO DO
					//TO DO sprintf( cNombreTablaOrigen, "caCarmov" );
					*/
					hr = StringCchPrintf(cNombreTablaOrigen,size_t(cNombreTablaOrigen),TEXT("caCarmov"));

					cNombreTablaOrigen[ 8 ] = 0;
					iPID = crearTmp( cNombreTablaOrigen, bContinuar );
					sTmpCaCarmov.Format( "tmp%s%d", cNombreTablaOrigen, iPID );
					if( iPID == -1 ) 
					{
						sSqlTxt.Format( "Error al crear tabla temporal %s", sTmpCaCarmov );//Error al crear tabla temporal %s
						AfxMessageBox( sSqlTxt );
						bContinuar = false;
					}
					if( bContinuar && iPID > 0 )
					{
						CInsTemCaCarmovAdics tmpCaCarmovSQL( &odbcTiendaNumero );
						tmpCaCarmovSQL.activarCols();
						tmpCaCarmovSQL.prepararInsert( sTmpCaCarmov );

						//TO DO sprintf( tmpCaCarmovSQL.clave, "G" );
						hr = StringCchPrintf(tmpCaCarmovSQL.clave,size_t(tmpCaCarmovSQL.clave),TEXT( "G"));
						tmpCaCarmovSQL.clave[ 1 ] = 0;
						//TO DO sprintf( tmpCaCarmovSQL.tipomovimiento, "8" );
						hr = StringCchPrintf(tmpCaCarmovSQL.tipomovimiento,size_t(tmpCaCarmovSQL.tipomovimiento),TEXT( "8"));
						tmpCaCarmovSQL.tipomovimiento[ 1 ] = 0;
						tmpCaCarmovSQL.tienda =(short int) iTienda;
						tmpCaCarmovSQL.ciudad = (short int) iCiudad;
						tmpCaCarmovSQL.cliente = lCliente;
						tmpCaCarmovSQL.caja = (short int) iCaja;
						tmpCaCarmovSQL.causabaja = (short int) iCausaBaja;
						//TO DO sprintf( tmpCaCarmovSQL.movtoseguro, "C" );
						hr = StringCchPrintf(tmpCaCarmovSQL.movtoseguro,size_t(tmpCaCarmovSQL.movtoseguro),TEXT( "C"));
						tmpCaCarmovSQL.movtoseguro[ 1 ] = 0;
						tmpCaCarmovSQL.folio = lFolio;
						//TO DO sprintf( tmpCaCarmovSQL.statusseguro, "%c", cStatusSeg );
						hr = StringCchPrintf(tmpCaCarmovSQL.statusseguro,size_t(tmpCaCarmovSQL.statusseguro),TEXT( "%c"),cStatusSeg);
						tmpCaCarmovSQL.statusseguro[ 1 ] = 0;					
						tmpCaCarmovSQL.edad = 0;
						tmpCaCarmovSQL.fecha.ponerFecha( iDiaActual, iMesActual, iAnioActual );
						tmpCaCarmovSQL.efectuo = lEmpleado;
						//TO DO sprintf( tmpCaCarmovSQL.ipcarteracliente,"%s",sServer );
						hr = StringCchPrintf(tmpCaCarmovSQL.ipcarteracliente,size_t(tmpCaCarmovSQL.ipcarteracliente),TEXT( "%S"),sServer);
						hr = StringCchPrintf(cNombreTablaOrigen,size_t(cNombreTablaOrigen),TEXT("caCarmov"));
						if ( iTipo == 1)
						{
							tmpCaCarmovSQL.bonificacion=0;
						}
						else
						{
							tmpCaCarmovSQL.bonificacion=77;
						}
						if( iFlagTieneAdicionales == 1 )
						{
							tmpCaCarmovSQL.tiposeguro[0] = '1';
							tmpCaCarmovSQL.flagseguroconyugal[0] = '1';
						}
						else
						{
							tmpCaCarmovSQL.tiposeguro[0] = '0';
							tmpCaCarmovSQL.flagseguroconyugal[0] = '0';
						}
						tmpCaCarmovSQL.tiposeguro[1] = 0;
						tmpCaCarmovSQL.flagseguroconyugal[1] = 0;

						if( tmpCaCarmovSQL.Insert() ) // Inserta registro del seguro titular
						{
							tmpCaCarmovSQL.Commit();
							if( iFlagTieneAdicionales == 1 )
							{
								CMaximo consultaFoliosAdics( &odbcCartera );
								sSqlTxt.Format( "SELECT folio FROM crSeguros WHERE cliente = %ld AND claveseguro = 'C' AND statusseguro = 'A' AND claveconyugal = 1 AND tiposeguro = 2", lCliente );

								consultaFoliosAdics.Exec( sSqlTxt );
								consultaFoliosAdics.activarCols();
								while( consultaFoliosAdics.leer() )
								{
									tmpCaCarmovSQL.folio = consultaFoliosAdics.Total;
									tmpCaCarmovSQL.tiposeguro[0] = '2';
									tmpCaCarmovSQL.tiposeguro[1] = 0;
									tmpCaCarmovSQL.flagseguroconyugal[0] = '1';
									tmpCaCarmovSQL.flagseguroconyugal[1] = 0;
									if( tmpCaCarmovSQL.Insert() ) // Inserta registro para los seguros adicionales
									{
										tmpCaCarmovSQL.Commit();
									}
									else
									{
										bContinuar = false;
										break;
									}
								}
							}
						}
						else
						{
							//Se obtiene el error
							sServer.TrimLeft();
							sServer.TrimRight();
							//TO DO sprintf(cIPDestino,"%s",sServer);
							hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
							cIPDestino[15] = 0;
							sSqlTxt.Format( "Insertar en tabla %s", sTmpCaCarmov );
							sSqlTxt.TrimLeft();
							sSqlTxt.TrimRight();
							//TO DO sprintf(cConsulta,"%s",sSqlTxt);
							hr = StringCchPrintf(cConsulta,size_t(cConsulta),TEXT("%s"),sSqlTxt);
							cConsulta[ sSqlTxt.GetLength() ] = 0;

							tmpCaCarmovSQL.odbc->GetLastError(tmpCaCarmovSQL.GetHstmt());
							grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "graboSeguros", cConsulta,lEmpleado,"Error #6227",tmpCaCarmovSQL.odbc,iMuestraMsg);
							bContinuar = false;
						}

						//actualizar_hora_movto( 1,999999 );   //gn_grmov.cpp //Ya no se usa.

						if( bContinuar )
						{
							iPasaTmp = pasarTmp( "cacarmov", iPID, bContinuar );
							if( bContinuar && iPasaTmp == 1 )
							{
								actualizarCrSeguros( iCausaBaja,lFolio );
							}
						}
					}				
				}
				else
				{
					//Crear tmp de caSegurosClientesNuevos
					//TO DO sprintf( cNombreTablaOrigen, "caSegurosClientesNuevos" );
					hr = StringCchPrintf(cNombreTablaOrigen,size_t(cNombreTablaOrigen),TEXT("caCarmov"));
					cNombreTablaOrigen[ 23 ] = 0;
					iPID = crearTmp( cNombreTablaOrigen, bContinuar );
					sTmpCaSegurosClientesNuevos.Format( "tmp%s%d", cNombreTablaOrigen, iPID );
					if( iPID == -1 ) 
					{
						sSqlTxt.Format( "Error al crear tabla temporal %s", sTmpCaSegurosClientesNuevos );//Error al crear tabla temporal %s
						AfxMessageBox( sSqlTxt );
						bContinuar = false;
					}
					if( bContinuar && iPID > 0 )
					{
						CInsertarTmpCaSegCteNvo tmpCaSegurosClientesNuevosSQL( &odbcTiendaNumero );
						tmpCaSegurosClientesNuevosSQL.activarCols();
						tmpCaSegurosClientesNuevosSQL.prepararInsert( sTmpCaSegurosClientesNuevos );

						//TO DO sprintf( tmpCaSegurosClientesNuevosSQL.clave, "G" );
						hr = StringCchPrintf(tmpCaSegurosClientesNuevosSQL.clave,size_t(tmpCaSegurosClientesNuevosSQL.clave),TEXT( "G" ));
						tmpCaSegurosClientesNuevosSQL.clave[ 1 ] = 0;
						//TO DO sprintf( tmpCaSegurosClientesNuevosSQL.tipomovimiento, "8" );
						hr = StringCchPrintf(tmpCaSegurosClientesNuevosSQL.tipomovimiento,size_t(tmpCaSegurosClientesNuevosSQL.tipomovimiento),TEXT( "8" ));
						tmpCaSegurosClientesNuevosSQL.tipomovimiento[ 1 ] = 0;
						tmpCaSegurosClientesNuevosSQL.cliente = lCliente;
						tmpCaSegurosClientesNuevosSQL.edad = 0 ;
						tmpCaSegurosClientesNuevosSQL.caja = (short int) iCaja;
						tmpCaSegurosClientesNuevosSQL.recibo = 0L; //En funcion PostgreSQL se le asigna.
						tmpCaSegurosClientesNuevosSQL.folio = lFolio;
						//TO DO sprintf( tmpCaSegurosClientesNuevosSQL.movtoseguro, "C" );
						hr = StringCchPrintf(tmpCaSegurosClientesNuevosSQL.movtoseguro,size_t(tmpCaSegurosClientesNuevosSQL.movtoseguro),TEXT("C"));
						tmpCaSegurosClientesNuevosSQL.movtoseguro[ 1 ] = 0;
						//TO DO sprintf( tmpCaSegurosClientesNuevosSQL.statusseguro, "%c", cStatusSeg );
						hr = StringCchPrintf(tmpCaSegurosClientesNuevosSQL.statusseguro,size_t(tmpCaSegurosClientesNuevosSQL.statusseguro),TEXT("%c"), cStatusSeg);
						tmpCaSegurosClientesNuevosSQL.statusseguro[ 1 ] = 0;
						tmpCaSegurosClientesNuevosSQL.causabaja = (short int) iCausaBaja;
						tmpCaSegurosClientesNuevosSQL.fechaventa.ponerFecha( iDiaActual, iMesActual, iAnioActual );
						tmpCaSegurosClientesNuevosSQL.tienda = (short int) iTienda;
						tmpCaSegurosClientesNuevosSQL.ciudad = (short int) iCiudad;
						tmpCaSegurosClientesNuevosSQL.fecha.ponerFecha( iDiaActual, iMesActual, iAnioActual );
						tmpCaSegurosClientesNuevosSQL.efectuo = lEmpleado;
						if( tmpCaSegurosClientesNuevosSQL.Insert() )
						{
							tmpCaSegurosClientesNuevosSQL.Commit();
						}
						else
						{
							//Se obtiene el error
							sServer.TrimLeft();
							sServer.TrimRight();
							//TO DO sprintf(cIPDestino,"%s",sServer);
							hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
							cIPDestino[15] = 0;
							sSqlTxt.Format( "Insertar en tabla %s", sTmpCaSegurosClientesNuevos );
							sSqlTxt.TrimLeft();
							sSqlTxt.TrimRight();
							//TO DO sprintf(cConsulta,"%s",sSqlTxt);
							hr = StringCchPrintf(cNombreTablaOrigen,size_t(cNombreTablaOrigen),TEXT("%s"),sSqlTxt);
							cConsulta[ sSqlTxt.GetLength() ] = 0;

							tmpCaSegurosClientesNuevosSQL.odbc->GetLastError(tmpCaSegurosClientesNuevosSQL.GetHstmt());
							grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "graboSeguros", cConsulta,lEmpleado,"Error #6228",tmpCaSegurosClientesNuevosSQL.odbc,iMuestraMsg);
							bContinuar = false;
						}
						//actualizar_hora_movto( 1,999999 );   //gn_grmov.cpp //Ya no se usa                    
						if( bContinuar )
						{
							iPasaTmp = pasarTmp( "casegurosclientesnuevos", iPID, bContinuar );
							if( bContinuar && iPasaTmp == 1 )
							{
								actualizarCrSeguros( iCausaBaja,lFolio );
							}
						}
					}
				}
			}
        }
		else
		{
			AfxMessageBox( "El cliente no tiene seguro club familiar" );//El cliente no tiene seguro club
		}
    }
}


int CDlgCancelarSeguroClub::crearTmp( char *cNombreTablaOrigen, bool &bContinuar )
{
	HRESULT hr = 0;
	CString sSqlTxt;
	int iPID = 0;

	bContinuar = true;

	sSqlTxt.Format( "SELECT gncreartablatmp('%s')", cNombreTablaOrigen );
	CConsultarPID crearTmpSQL( &odbcTiendaNumero );
	if( crearTmpSQL.Exec( sSqlTxt ) )
	{
		crearTmpSQL.activarCols();
		if( crearTmpSQL.Leer() )
		{
			iPID = crearTmpSQL.pid;
		}
	}
	else
	{
		//Se obtiene el error
		sServer.TrimLeft();
		sServer.TrimRight();
		//TO DO sprintf(cIPDestino,"%s",sServer);
		hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
		cIPDestino[15] = 0;
		sSqlTxt.TrimLeft();
		sSqlTxt.TrimRight();
		//TO DO sprintf(cConsulta,"%s",sSqlTxt);
		hr = StringCchPrintf(cConsulta,size_t(cConsulta),TEXT("%s"),sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		crearTmpSQL.odbc->GetLastError(crearTmpSQL.GetHstmt());
		grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "crearTmp", cConsulta,lEmpleado,"Error #6229",crearTmpSQL.odbc,iMuestraMsg);
		bContinuar = false;
	}

	return iPID;
}

int CDlgCancelarSeguroClub::pasarTmp( char *cNombreTablaOrigen, int iPID, bool &bContinuar )
{
	HRESULT hr = 0;
	CString sSqlTxt;
	int iFlagPaso = 0;

	bContinuar = true;	
    if (iSistema==3)
	{
		
		sSqlTxt.Format( "SELECT cncancelarseguroclub('%s','%d','%d','%d','%ld');", cNombreTablaOrigen, iCaja, FOLIOC_RECIBO, iPID, lCliente );
		//sSqlTxt.Format( "SELECT cncancelarseguroclub('%s','%d','%d','%d','%ld');", cNombreTablaOrigen, iCaja, FOLIOC_RECIBOSEGURO, iPID, lCliente );
	}
	else
	{
		sSqlTxt.Format( "SELECT cncancelarseguroclub('%s','%d','%d','%d','%ld');", cNombreTablaOrigen, iCaja, FOLIO_RECIBOSEGURO, iPID, lCliente );
	}

	CConsultarPID pasarTmpSQL( &odbcTiendaNumero );
	if( pasarTmpSQL.Exec( sSqlTxt ) )
	{
		pasarTmpSQL.activarCols();
		if( pasarTmpSQL.Leer() )
		{
			iFlagPaso = pasarTmpSQL.pid;
		}
	}
	else
	{
		//Se obtiene el error
		sServer.TrimLeft();
		sServer.TrimRight();
		//TO DO sprintf(cIPDestino,"%s",sServer);
		hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
		cIPDestino[15] = 0;
		sSqlTxt.TrimLeft();
		sSqlTxt.TrimRight();
		//TO DO sprintf(cConsulta,"%s",sSqlTxt);
		hr = StringCchPrintf(cConsulta,size_t(cConsulta),TEXT("%s"),sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		pasarTmpSQL.odbc->GetLastError(pasarTmpSQL.GetHstmt());
		grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "pasarTmp", cConsulta,lEmpleado,"Error #6230",pasarTmpSQL.odbc,iMuestraMsg);
		bContinuar = false;
	}

	return iFlagPaso;
}

void CDlgCancelarSeguroClub::actualizarCrSeguros( int iCausaBaja,long lFolio )
{
	CString sSqlTxt;
	HRESULT hr = 0;

	sSqlTxt.Format( "SELECT cncrcancelarseguroclub('%ld','%d','%d','%d','%ld','%ld');", lCliente, iCausaBaja, iDiaActual, iMesActual, iAnioActual, lFolio );
	CConsultarPID actCrSegurosSQL( &odbcCartera ); //conexión a cartera
	if( !actCrSegurosSQL.Exec( sSqlTxt ) )
	{
		
		//Se obtiene el error
		sServer.TrimLeft();
		sServer.TrimRight();
		//TO DO sprintf(cIPDestino,"%s",sServer);
		hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
		cIPDestino[15] = 0;
		sSqlTxt.TrimLeft();
		sSqlTxt.TrimRight();
		//TO DO sprintf(cConsulta,"%s",sSqlTxt);
		hr = StringCchPrintf(cConsulta,size_t(cConsulta),TEXT("%s"),sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		actCrSegurosSQL.odbc->GetLastError(actCrSegurosSQL.GetHstmt());
		grabarMensajeError( "N", iCaja, cIPDestino, "CN0027", "CDlgCancelarSeguroClub", "pasarTmp", cConsulta,lEmpleado,"Error #6231",actCrSegurosSQL.odbc,iMuestraMsg);
	}
	else
	{
		grabarCarmovx( iCausaBaja );
		iAllOk = 2;
	}
}

/*bool CDlgCancelarSeguroClub::bucarClienteCartera(void)
{
    CString sSqlTxt;
    bool bContinua=false;
	char cIpHuellasCtes[20], cIpGlobalTiendas[20], cIpHllasPasstda[20], cCadenaPaso[16];
	char cSqlTxt[255],cNombre[20],cPaterno[20],cMaterno[20],cSexo[3];
	
	SecureZeroMemory(cIpHuellasCtes,' ',sizeof(cIpHuellasCtes));
	SecureZeroMemory(cIpGlobalTiendas,' ',sizeof(cIpGlobalTiendas));
	SecureZeroMemory(cIpHllasPasstda,' ',sizeof(cIpHllasPasstda));

	if ( consultarIpServidor( &odbc, cIpHuellasCtes, SERV_HUELLASCLIENTES, cSqlTxt ) )
	{
		if ( consultarIpServidor( &odbc, cIpGlobalTiendas, SERV_GLOBALTIENDAS, cSqlTxt ) )
		{
			if ( consultarIpServidor( &odbc, cIpHllasPasstda, SERV_HLLASPASSTDA, cSqlTxt ) )
			{
				bContinua=true;
			}
		}
	}

	if ( bContinua )
	{
		CNombreSexFecCrCliente xCartera(&odbc_1) ;
	    
		sSqlTxt.Format("SELECT nombre, apellidopaterno, apellidomaterno, sexo, fechanacimiento FROM crcliente WHERE cliente = %ld",lCliente);
		if(xCartera.Exec(sSqlTxt))
		{
			xCartera.activarCols();
			if(xCartera.Leer())
			{
				
				SecureZeroMemory(cComandoCNW,' ',sizeof(cComandoCNW));			
				if ( !access("c:\\SYS\\PROGS\\CNW7.EXE", 0 ) == 0 )
				{			
					AfxMessageBox( "No se encuentra módulo CNW7" );
				}			
				
				SecureZeroMemory(cCadenaPaso,' ',sizeof(cCadenaPaso));
				memcpy(cCadenaPaso,xCartera.nombre,15);
				if( checarBlancos( cCadenaPaso,15 )==0 ) 
				{
					cCadenaPaso[0]='.';
				}
				formarNombres(cCadenaPaso);
				memcpy(cNombre,cCadenaPaso,15);
				cNombre[15]=0;            
				
				memcpy(cCadenaPaso,xCartera.apellidopaterno,15);
				if( checarBlancos( cCadenaPaso,15 )==0 )
				{
					cCadenaPaso[0]='.';
				}
				formarNombres(cCadenaPaso);
				memcpy(cPaterno,cCadenaPaso,15);
				cPaterno[15]=0;            
				
				memcpy(cCadenaPaso,xCartera.apellidomaterno,15);
				if( checarBlancos( cCadenaPaso,15 )==0 )
				{
					cCadenaPaso[0]='.';
				}
				formarNombres(cCadenaPaso);
				memcpy(cMaterno,cCadenaPaso,15);
				cMaterno[15]=0;
				memcpy(&cSexo[0],xCartera.sexo,1);			
				cSexo[1]=0;

				//TO DO sprintf(cComandoCNW,"%04d %09ld %s %s %s %s 5 %s %s %s", iTienda, lCliente, cNombre, cPaterno, cMaterno, cSexo, cIpHuellasCtes, cIpGlobalTiendas, cIpHllasPasstda);

				bContinua=true;

			}

			if( bContinua == false )
			{
				AfxMessageBox("Cliente no se encontro en la cartera",MB_ICONINFORMATION);
			}

		}
		else
		{
			xCartera.odbc->GetLastError( xCartera.GetHstmt() );
			grabarMensajeError("N",iCaja,cIPDestino,"CN0027","CDlgCancelarSeguroClub","buscarClienteCartera",cSqlTxt,lEmpleado,"ERROR AL CONSULTAR CRHUELLAS",&odbc_1,iMuestraMsg );		
			bContinua= false;
	        
		}
	}

    return  bContinua;
}*/

static int pantallaInvalida()
{
	int iFlag = 0, iRespuesta = 0;
	char cMensajeOut[MAX_BUFFER_XML] = {0};

	iRespuesta = MessageBox(NULL, "HUELLA DEL CLIENTE NO HA SIDO RECONOCIDA, DESEA AUTORIZAR GERENTE ?", "ATENCION", MB_YESNO|MB_ICONQUESTION);//HUELLA DEL CLIENTE NO HA SIDO RECONOCIDA, DESEA AUTORIZAR GERENTE ?
	switch (iRespuesta)
	{
		case IDYES:
				iFlag = 8; // Lo que era el F8
			break;

		case IDNO:
				iFlag = 10; // Lo que era el F10
			break;
		
		default:
			break;
	}
	return iFlag;
}

int CDlgCancelarSeguroClub::checarHuellaCliente(long lCliente,int iCaja,long lEmpleado,int iMuestraMsg,int iTienda)
{
	HRESULT hr = 0;
bool bRespuesta, bProceso=true;
CString  sNombre,sApellidoPaterno,sApellidoMaterno,sTexto,sConsulta,sSqlTxt,sServer;
char cSexo=' ',/*cArchivo[80],*/cTda[5],cCliente[15],/*cRespuesta[150],cRespuesta2[80],*/cConsulta[1002],cIPDestino[22];
char cNombre[20],cApellidoPaterno[20],cApellidoMaterno[20],/*cIp1[20],cIp2[20],cIp3[20],*/ cSql[255];
int  /*i=0,*/iFlag=0, iFlagInvalido=0;//, iFlagResp=0, iFlagResp2=0;
long /*lHuella=0,*/ lGteHuella=0, lCteParametro=0L, lFlagResp1=0L, lFlagResp2=0L;
char cMensajeOut[MAX_BUFFER_XML] = {0};
long lEmpleadox = 0; 
int iFlagRecaptura = 0;

	//SecureZeroMemory(cRespuesta,0, sizeof(cRespuesta));
	//SecureZeroMemory(cRespuesta2,0, sizeof(cRespuesta2));
	SecureZeroMemory(cTda, sizeof(cTda));
	SecureZeroMemory(cCliente, sizeof(cCliente));
	SecureZeroMemory(cNombre, sizeof(cNombre));
	SecureZeroMemory(cApellidoPaterno, sizeof(cApellidoPaterno));
	SecureZeroMemory(cApellidoMaterno,sizeof(cApellidoMaterno));
	SecureZeroMemory(cSql, sizeof(cSql));		
	//Templ Templates, templ;
	//SecureZeroMemory(&Templates, ' ', sizeof(Templates));
	//SecureZeroMemory(&templ, ' ', sizeof(templ));		

	sSqlTxt.Format(" SELECT nombre, apellidopaterno, apellidomaterno, ciudad, colonia, puntualidad,  "
		           " situacionespecial,causasitesp,sexo,fechanacimiento,ingresomensual FROM crcliente "
				   " WHERE cliente = %ld ", lCliente);

	CConsultarCliente consultarClienteSQL(&odbcCartera);
	if (!consultarClienteSQL.Exec(sSqlTxt))
	{
		consultarClienteSQL.odbc->GetLastError(consultarClienteSQL.GetHstmt());
		//TO DO sprintf(cConsulta,"%s",sSqlTxt);
		hr = StringCchPrintf(cConsulta,size_t(cConsulta),TEXT("%s"),sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;
		//TO DO sprintf(cIPDestino,"%s",sServer);
		hr = StringCchPrintf(cIPDestino,size_t(cIPDestino),TEXT("%s"),sServer);
		cIPDestino[15] = 0;
		grabarMensajeError( "N",iCaja,cIPDestino,"MenuSeguroClub","CDlgMebuSeguroClub","desplegarCliente",cConsulta,lEmpleado,"Error #6232",consultarClienteSQL.odbc,iMuestraMsg );
	    bRespuesta = false;
	}
	else
    {
		consultarClienteSQL.activarCols();
		if( consultarClienteSQL.Leer() )
		{
			sNombre.Format("%s",consultarClienteSQL.nombre);
			sNombre.Trim();			
			sApellidoPaterno.Format("%s",consultarClienteSQL.apellidopaterno);
			sApellidoPaterno.Trim();			
			sApellidoMaterno.Format("%s",consultarClienteSQL.apellidomaterno);
			sApellidoMaterno.Trim();						
			cSexo = consultarClienteSQL.sexo[0];
			sNombre.Trim();
			sApellidoPaterno.Trim();
			sApellidoMaterno.Trim();
			//TO DO sprintf(cNombre, "%s", sNombre);
			hr = StringCchPrintf(cNombre,size_t(cNombre),TEXT( "%s"), sNombre);
			//TO DO sprintf(cApellidoPaterno, "%s", sApellidoPaterno);
			hr = StringCchPrintf(cApellidoPaterno,size_t(cApellidoPaterno),TEXT("%s"), sApellidoPaterno);
			//TO DO sprintf(cApellidoMaterno, "%s", sApellidoMaterno);
			hr = StringCchPrintf(cApellidoMaterno,size_t(cApellidoMaterno),TEXT("%s"),sApellidoMaterno);
		}
	}			

	// VentaSeguroClub
	/*SecureZeroMemory(cArchivo, 0, sizeof(cArchivo));
	nombreArchivo( "CNW7.EXE", cArchivo, DIRECTORIO_PROGS );
	///Huella de cliente
	if ( access( cArchivo, 0 ) != 0 )
	{
		AfxMessageBox("HABLAR A PROGRAMACION, NO EXISTE EL MODULO CNW7.EXE");
	}
	else
	{
		if ( abrirConexionHuellasClientes(&odbc) == true )
		{					
			{
				CCrHuellas consultarcrHuella( &odbc_3 ); // bd huella cliente
				sConsulta.Format(" SELECT cliente, flagadicional, templatededoderecho001, templatededoderecho002, templatededoderecho003, templatededoderecho004, templatededoderecho005, templatededoderecho006, templatededoderecho007, templatededoderecho008, templatededoderecho009, templatededoderecho010, templatededoderecho011, templatededoderecho012, templatededoderecho013, templatededoderecho014, templatededoderecho015, templatededoderecho016, templatededoderecho017, templatededoderecho018, templatededoderecho019, templatededoderecho020,"
								" templatededoderecho021, templatededoderecho022, templatededoderecho023, templatededoderecho024, templatededoderecho025, templatededoderecho026, templatededoderecho027, templatededoderecho028, templatededoderecho029, templatededoderecho030, templatededoderecho031, templatededoderecho032, templatededoderecho033, templatededoderecho034, templatededoderecho035, templatededoderecho036, templatededoderecho037, templatededoderecho038, templatededoderecho039, templatededoderecho040, templatededoderecho041, templatededoderecho042, templatededoderecho043,"
								" templatededoderecho044, templatededoderecho045, templatededoderecho046, templatededoderecho047, templatededoderecho048, templatededoderecho049, templatededoderecho050, templatededoderecho051, templatededoderecho052, templatededoderecho053, templatededoderecho054, templatededoderecho055, templatededoderecho056, templatededoderecho057, templatededoderecho058, templatededoderecho059, templatededoderecho060, templatededoderecho061, templatededoderecho062, templatededoderecho063, templatededoderecho064, templatededoderecho065, templatededoderecho066,"
								" templatededoderecho067, templatededoderecho068, templatededoderecho069, templatededoderecho070, templatededoderecho071, templatededoderecho072, templatededoderecho073, templatededoderecho074, templatededoderecho075, templatededoderecho076, templatededoderecho077, templatededoderecho078, templatededoderecho079, templatededoderecho080, templatededoderecho081, templatededoderecho082, templatededoderecho083, templatededoderecho084, templatededoderecho085, templatededoderecho086, templatededoderecho087, templatededoderecho088"
								" FROM crhuellas WHERE cliente = %ld", lCliente );
				if ( consultarcrHuella.Exec( sConsulta ) )
				{
					consultarcrHuella.activarCols();
					if ( consultarcrHuella.Leer() )
					{
						unlink( "c:\\template\\template.02" );
						{																			
							SecureZeroMemory(cRespuesta, ' ', sizeof(cRespuesta));
							memcpy( &Templates.templates1, &consultarcrHuella.templatededoderecho, 700 );
							SecureZeroMemory(cRespuesta2, 0, sizeof(cRespuesta2));
							for( int i = 0; i < 10; i++ )
							{
								cRespuesta2[i] = Templates.templates1[i]+'0';
							}
							lHuella = valorCampo( cRespuesta2, 9 );
							if ( lHuella == 999999999 )
							{
								//huella invalida
								iFlag = 1;
								iFlagInvalido = 1;
							}
							//TO DO sprintf( cTda, "%04d", iTienda );
							//TO DO sprintf( cCliente, "%09d", lCliente );
							//TO DO sprintf(cRespuesta,"%04d %09d",iTienda,lCliente);
							cRespuesta[14]= ' ';
							checarNulos( cNombre,15 );
							memcpy(cRespuesta2,cNombre,15);
							if ( checarBlancos( cRespuesta2, 15 ) == 0 )
								cRespuesta2[14]='.';
								formarNombres(cRespuesta2);    //cnwcnlon.cpp
								memcpy(&cRespuesta[15],cRespuesta2,15);
													
								checarNulos( cApellidoPaterno,15 );
								memcpy(cRespuesta2,cApellidoPaterno,15);											
							if ( checarBlancos( cRespuesta2,15 ) == 0 )
								cRespuesta2[0] = '.';
								formarNombres(cRespuesta2);    //cnwcnlon.cpp
								memcpy(&cRespuesta[31],cRespuesta2,15);
																	
								checarNulos( cApellidoMaterno,15 );
								memcpy(cRespuesta2,cApellidoMaterno,15);
								cRespuesta2[15]=0;
							if ( checarBlancos( cRespuesta2,15 ) == 0 )
								cRespuesta2[0] = '.';
								formarNombres(cRespuesta2);    //cnwcnlon.cpp
								memcpy(&cRespuesta[47],cRespuesta2,15);
																						
								cRespuesta[63] = cSexo;
							if( cRespuesta[63] == ' ' ) cRespuesta[63] = '.';
					                                  
								cRespuesta[64] = ' ';
								cRespuesta[65] = '5';
								cRespuesta[66] = 0;

								//formar archivo para comparar
								C_Archivo arc_templ;
								arc_templ.abrir( "c:\\template\\template.02", sizeof(templ));
								SecureZeroMemory(&templ,0,sizeof(templ));
								if ( consultarcrHuella.cliente == lCliente )
								{
									memcpy( templ.templates1, &consultarcrHuella.templatededoderecho, 700 );
									arc_templ.grabar(&templ,0L);
									arc_templ.cerrar();
								}
															
								if ( iFlagInvalido == 0 ) //si no es huella invalida
								{								
									unlink("c:\\template\\respuest.dat");
									spawnl( _P_WAIT,"C:\\SYS\\PROGS\\CNW7.EXE","C:\\SYS\\PROGS\\CNW7.EXE", cRespuesta , cIp1, cIp2, cIp3, NULL);
									iFlagResp = verificarRespuestaHuella(lGteHuella); // gnwvehue.cpp									
									if ( iFlagResp == 1 )
									{
										iFlag = 2; //es correcta la huella																																			
									}
									else
									{
										if ( iFlagResp == 2 )
										{
											//huella invalida pero se autoriza la venta
											iFlag = 1;																											
											sTexto.Format( "ATENCION: VERIFICAR DATOS DEL CLIENTE. ¿DESEA CONTINUAR?" );
											while ( AfxMessageBox( sTexto, MB_YESNO|MB_ICONQUESTION ) != IDYES )
											{
															
											}
										}
										else
										{																						
											//incorrecta la huella capturada
											iFlag = 0;
											if ( iTipo == 0 )
											{												
												sTexto.Format( "HUELLA DEL CLIENTE NO HA SIDO RECONOCIDA, DESEA AUTORIZAR GERENTE ?" );
												if ( AfxMessageBox( sTexto, MB_YESNO|MB_ICONQUESTION ) == IDYES )
												{
													//llamar al cnw para validar huella del gerente																																																																																																													
													validarHuellaEmpleadoGte( &odbc, lGteHuella, 1, 13, 0, iTienda, SISTEMA_CLIENTES_NUEVOS, iCaja );  //gnwvahue.cpp																																																																											
													if( lGteHuella < 16 )
													{
														pintarMensajesErrorPasstda( lGteHuella ); //gnwvahue.cpp
													}
													else
													{
														iFlag = 3; //si es correcta
													}																				
												}
											}
											else
											{
												sTexto.Format( "ATENCION: FAVOR DE LLAMAR A GERENTE DEL AREA DE CAJAS PARA CHECAR REGISTRO DE HUELLAS DEL CLIENTE. SOLO EL GERENTE PUEDE AUTORIZAR LA ENTREGA DE TARJETA. ¿DESEA VALIDAR GERENTE?" );
												if ( AfxMessageBox( sTexto, MB_YESNO|MB_ICONQUESTION ) == IDYES )
												{																					
													validarHuellaEmpleadoGte( &odbc, lGteHuella, 1, 13, 0, iTienda, SISTEMA_CLIENTES_NUEVOS, iCaja );  //gnwvahue.cpp																													
													if( lGteHuella < 16 )
													{
														pintarMensajesErrorPasstda( lGteHuella ); //gnwvahue.cpp
													}
													else
													{
														iFlag = 3; //si es correcta
													}
												}
											}
										}
									}
								}
								else
								{
									//Solo se pide la huella del gerente por que la huella del cliente es invalida
									if ( iTipo == 0 )
									{
										//TO DO sprintf( cTda, "%03d", iTienda );
										sTexto.Format( "QUE GERENTE VERIFIQUE IDENTIFICACION DEL CLIENTE Y DECIDE. ¿DESEA AUTORIZAR?" );
										if ( AfxMessageBox( sTexto, MB_YESNO|MB_ICONQUESTION ) == IDYES )
										{
											//llamar al cnw para validar huella del gerente																						
											validarHuellaEmpleadoGte( &odbc, lGteHuella, 1, 13, 0, iTienda, SISTEMA_CLIENTES_NUEVOS, iCaja );  //gnwvahue.cpp
											if( lGteHuella < 16 )
											{
												pintarMensajesErrorPasstda( lGteHuella ); //gnwvahue.cpp
											}
											else
											{
												iFlag = 1;
											}
										}
										else
										{
											iFlag=0;
										}
									}
								}
								unlink("c:\\template\\template.02");
							}
						}
						else
						{
							sTexto.Format( "HUELLA DEL CLIENTE NO HA SIDO RECONOCIDA, DESEA AUTORIZAR GERENTE ?" );
							if ( AfxMessageBox( sTexto, MB_YESNO|MB_ICONQUESTION ) == IDYES )
							{
								validarHuellaEmpleadoGte( &odbc, lGteHuella, 1, 13, 0, iTienda, SISTEMA_CLIENTES_NUEVOS, iCaja );  //gnwvahue.cpp																		
								if( lGteHuella < 16 )
								{
									pintarMensajesErrorPasstda( lGteHuella ); //gnwvahue.cpp
								}
								else
								{
									iFlag = 3;
								}
							}
							else
							{
								iFlag=0;
							}
						}
					}
					else
					{
						consultarcrHuella.odbc->GetLastError(consultarcrHuella.GetHstmt());
						//TO DO sprintf(cConsulta,"%s",sConsulta);
						cConsulta[ sConsulta.GetLength() ] = 0;
						//TO DO sprintf(cIPDestino,"%s",sServer);
						cIPDestino[15] = 0;
						grabarMensajeError( "N",iCaja,cIPDestino,"MenuSeguroClub","CDlgMenuSeguroClub","validarHuellaCliente",cConsulta,lEmpleado,"ERROR EN LA CONSULTA",consultarcrHuella.odbc,iMuestraMsg );
					}
				}
				cerrarConexionHuellasClientes();
			}
		}	*/
	
	llamarChW( 5, lCliente, iTienda, iCiudad, iCaja, iSistema, cNombre, cApellidoPaterno, cApellidoMaterno,
		       cSexo, &odbcTiendaNumero, cSql, bProceso, lCteParametro, lFlagResp1, lFlagResp2, lEmpleadox, iFlagRecaptura ); // gnwchwdl.cpp
	if ( lFlagResp2 != 1 )
	{
		sTexto.Format( "HUELLA DEL CLIENTE NO HA SIDO RECONOCIDA. ¿AUTORIZACION DEL GERENTE?" );//HUELLA DEL CLIENTE NO HA SIDO RECONOCIDA. ¿AUTORIZACION DEL GERENTE?
		if ( AfxMessageBox( sTexto, MB_YESNO|MB_ICONQUESTION ) == IDYES )
		{
			//llamar al cnw para validar huella del gerente																						
			//validarHuellaEmpleadoGte( &odbc, lGteHuella, 1, 15, 0, iTienda, SISTEMA_CLIENTES_NUEVOS, iCaja );  //gnwvahue.cpp
			validarHuellaEmpleadoGte01( &odbcTiendaNumero, lGteHuella, 1, MOVTO_MENUSEGURO, 0, iTienda, SISTEMA_CLIENTES_NUEVOS, iCaja,"CN0027.DLL");
			if( lGteHuella == -1 )
			{
				lGteHuella=0L;	
				iFlag=0;
				AfxMessageBox("NO HAY ENLACE CON EL SERVIDOR DE HUELLAS");//NO HAY ENLACE CON EL SERVIDOR DE HUELLAS
			}
			else
			{
				if( lGteHuella < 16 )
				{
					iFlag=0;
					pintarMensajesErrorPasstda( lGteHuella ); //gnwvahue.cpp
				}
				else
				{
					iFlag = 1;
				}
			}
		}
		else
		{
			iFlag=0;
		}	
	}
	else
	{
		iFlag = 1;
	}
	return(iFlag);
}
void CDlgCancelarSeguroClub::OnEnChangeTipo()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogoML::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
bool CDlgCancelarSeguroClub::grabarCarmovx( int iCausaBaja )
{
	HRESULT hr = 0;
	bool bContinuar = false;
	CString sTexto;
	int iLongitud=0,iRespuesta=0;
	char cDll[64] = {0};
    char cArgvIN1[1024] = {0}, cArgvIN2[1024] = {0};
    char cArgvOUT1[1024] = {0}, cArgvOUT2[1024] = {0};
	long lRecibo = 0L;
	struct EstructuraRespuesta
	{
		int iSalida;
	};	

	EstructuraRespuesta estructurarespuesta;
									
		ServicioInetCarmovx grabarcarmovx;
		SParametros argv;

		SecureZeroMemory( &argv, sizeof( argv ) );
		SecureZeroMemory( &grabarcarmovx, sizeof( grabarcarmovx ) );

		argv.iLink = generarLink();
		argv.iNumSistema = 20506;   //puerto cartera central
		argv.iFlagServicio = 31;
		argv.iFlagGeneral = 3; //Si se va a esperar que termine la ejecucion del servicio
		sTexto.Format("%s",cIpServidorCartera);
		sTexto.Trim();
		iLongitud = sTexto.GetLength();
		//TO DO sprintf( argv.sServer, "%s", sTexto );
		hr = StringCchPrintf(argv.sServer,size_t(argv.sServer),TEXT("%s"), sTexto);

		grabarcarmovx.sTipoMensaje=2;
		grabarcarmovx.iTipoOpcion=1;
		//TO DO sprintf( grabarcarmovx.IpServidor , "%s", cIpServidorCartera );
		hr = StringCchPrintf(grabarcarmovx.IpServidor,size_t(grabarcarmovx.IpServidor),TEXT("%s"),cIpServidorCartera);

		grabarcarmovx.cTipoMovimiento = '8';

		grabarcarmovx.iCliente=lCliente;
		grabarcarmovx.iImporte=0;
		grabarcarmovx.iInteres=0;
		grabarcarmovx.tFechaDia=(short)iDiaActual;
		grabarcarmovx.tFechaMes=(short)iMesActual;
		grabarcarmovx.tFechaAno=(short)iAnioActual;
		grabarcarmovx.iFactura=lFolio;				

		grabarcarmovx.iTienda=(short)iTienda;
		grabarcarmovx.iPlazo=0;
		grabarcarmovx.iNumeroArticulos=0;
		grabarcarmovx.iDiaPago=0;
		grabarcarmovx.iSaldoCuenta=0;
		grabarcarmovx.cClave = 'G';
		grabarcarmovx.cArea = 'N';
		grabarcarmovx.iPlazoConvenio=0;
		grabarcarmovx.iEfectuo=lEmpleado;
		mem_cpy(grabarcarmovx.cClaveAjuste,"  ",2);

		grabarcarmovx.tFechaSaldaConDia=1;
		grabarcarmovx.tFechaSaldaConMes=1;
		grabarcarmovx.tFechaSaldaConAno=1900;
		grabarcarmovx.iVencidoInicial=0;
		grabarcarmovx.iSaldoInicial=0;
		grabarcarmovx.cTipoConvenio = ' ';
		grabarcarmovx.cSubTipoConvenio = ' ';
		grabarcarmovx.iImporteSaldaCon=0;
		obtenerFolioRecibo( lCliente, iCausaBaja, lFolio, lRecibo );
		grabarcarmovx.iFolio=lRecibo;
		grabarcarmovx.tFechaNacimientoDia=1;
		grabarcarmovx.tFechaNacimientoMes=1;
		grabarcarmovx.tFechaNacimientoAno=1900;
		grabarcarmovx.tFechaVencimientoDia=1;
		grabarcarmovx.tFechaVencimientoMes=1;
		grabarcarmovx.tFechaVencimientoAno=1900;
		grabarcarmovx.cFlagSeguroConyugal = '0';
		grabarcarmovx.iCantidadSeguros=0;
		grabarcarmovx.cMovtoSeguro = 'C';
		grabarcarmovx.iCaja=(short)iCaja;
		grabarcarmovx.iCajaOriginal=(short)iCaja;
		grabarcarmovx.iCiudadTiendaMov = (short)iCiudad;
		grabarcarmovx.cTipoGrabado='T';

		mem_cpy( cArgvIN1, &argv, sizeof( argv ) );
		mem_cpy( cArgvIN2, &grabarcarmovx, sizeof( grabarcarmovx ) );

		nombreArchivo( "GN0063", cDll, DIRECTORIO_GN );

		{
			CargarDLL dll( cDll, "GN0063", cArgvIN1, cArgvIN2, cArgvOUT1, cArgvOUT2 );

			iRespuesta = dll.getResultado();
			if( iRespuesta == 1 )
			{
				mem_cpy( &estructurarespuesta, cArgvOUT1, sizeof( estructurarespuesta ) );
				if( estructurarespuesta.iSalida==1 )
				{							
					bContinuar=true;					
				}
			}
		}

	return bContinuar;
}

bool CDlgCancelarSeguroClub::obtenerFolioRecibo( long lCliente, int iCausaBaja, long lFolio, long &lRecibo )
{
	CString sSqlTxt;
	bool bContinuar = true;

	sSqlTxt.Format( "SELECT recibo FROM casegurosclientesnuevos where caja = %d and cliente = %d and folio = %d and causabaja = %d and tipomovimiento = '8' ", iCaja, lCliente, lFolio, iCausaBaja );
	
	CMaximo reciboSQL( &odbcTiendaNumero );  //conexión a tienda.nnnn

	if( reciboSQL.Exec( sSqlTxt ) )
	{
		reciboSQL.activarCols();
		if( reciboSQL.Leer() )
		{
			lRecibo = reciboSQL.Total;
			if ( lRecibo <= 0L ) lRecibo = 0L;
		}
	}
	else
	{
		reciboSQL.odbc->GetLastError( reciboSQL.GetHstmt() );
		grabarMensajeError( "N", iCaja,(LPTSTR)(LPCTSTR)sServer, "CN0016","CDlgCambiarDomicilioOS","leerFechaGnDominio",(LPTSTR)(LPCTSTR)sSqlTxt,lEmpleado,"Error #6233",reciboSQL.odbc,iMuestraMsg );
		bContinuar = false;		
	}

	return bContinuar;
}


void CDlgCancelarSeguroClub::fObtenerMensajeSeguro()
{
	HRESULT hr = 0;
	char cSql[100];
	CConsultarMensajeSeguro consultaMensajeSeguro(&odbcTiendaNumero);
	SecureZeroMemory(cMensajeSeguro,sizeof(cMensajeSeguro));
	SecureZeroMemory(cSql,sizeof(cSql));
	//TO DO sprintf(cSql,"SELECT des_mensaje FROM cat_mensajes WHERE idu_tipomensaje = 378");
	hr = StringCchPrintf(cSql,size_t(cSql),TEXT("SELECT des_mensaje FROM cat_mensajes WHERE idu_tipomensaje = 378"));

	if(consultaMensajeSeguro.Exec(cSql))
	{
		consultaMensajeSeguro.activarCols();
		if(consultaMensajeSeguro.leer())
		{
			/*
			//TO DO sprintf( cMensajeSeguro,"%s",consultaMensajeSeguro.des_mensaje );
			*/
			hr = StringCchPrintf(cMensajeSeguro,size_t(cMensajeSeguro),TEXT("%s"),consultaMensajeSeguro.des_mensaje);
			
			AfxMessageBox( cMensajeSeguro, MB_ICONINFORMATION );
		}
	}
}