// DlgCancelarSeguroClub.h: archivo de encabezado
//

#pragma once
#include "afxwin.h"

#include "sysCancelarSeguroClub.hpp"
#include "DialogoML.h"

#define MENSAJE_1001	1
#define MENSAJE_1002	2
#define MENSAJE_1003	3
#define MENSAJE_1004	4
#define MENSAJE_1005	5
#define MENSAJE_1006	6
#define MENSAJE_1007	7
#define MENSAJE_1008	8
#define MENSAJE_1009	9
#define MENSAJE_1010	10
#define MENSAJE_1011	11
#define MENSAJE_1012	12
#define MENSAJE_1013	13
#define MENSAJE_1014	14
#define MENSAJE_1015	15

// Cuadro de diálogo de CDlgCancelarSeguroClub
class CDlgCancelarSeguroClub : public CDialogoML
{
// Construcción
public:
	CDlgCancelarSeguroClub(CWnd* pParent = NULL);	// Constructor estándar

	//FUNCIONES
	void asignarFoco();
	void graboSeguros( long lCliente, int iCausaBaja, long lFolio );
	void actualizarCrSeguros( int iCausaBaja,long lFolio );

	bool validarControl(char *cCadena);
	bool validarControles();
	bool validarClick(int nTmpFocus);
	bool obtenerCdFechaCoppel();
	bool buscaSeguroCnsegCarmov( int iTabla, long lCliente, int &iSegCnseg );
	bool buscaSeguroCartera( long lCliente, int &iSegCartera, int &iSegCancelado, char &cStatusSeguro, int &iFlagTieneAdicionales );
	bool bucarClienteCartera(void);
	int  crearTmp( char *cNombreTablaOrigen, bool &bContinuar );
	int  pasarTmp( char *cNombreTablaOrigen, int iPID, bool &bContinuar );
	int  crearArchivoHuellas();	
	int  checarHuellaCliente(long lCliente,int iCaja,long lEmpleado,int iMuestraMsg,int iTienda);
	bool grabarCarmovx( int iCausaBaja );
	bool obtenerFolioRecibo( long lCliente, int iCausaBaja, long lFolio, long &lRecibo );
	void fObtenerMensajeSeguro();

	//VARIABLES
	char cIPDestino[22], cConsulta[1002],cComandoCNW[150],cIpServidorCartera[25],cMensajeSeguro[1026];
	CString sServer, sTmpCaCarmov, sTmpCaSegurosClientesNuevos,sFechaGn;
	int iTienda, iCaja, iSistema, iMuestraMsg, iCausa, iControles, iFoco, iCiudad;
	int iDiaActual, iMesActual, iAnioActual, iAllOk, iTipo;
	long lEmpleado, lCliente, lFolio;
	bool ShiftTab;

// Datos del cuadro de diálogo
    enum { IDD = IDD_DLGCANCELARSEGUROCLUB };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;
	CStatic m_barraMsj, m_textoMsj;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_causa;
	CEdit m_cliente;
	CEdit m_folio;
	CEdit m_nombreCliente;
	CButton m_escSalir;
	CButton m_f10Aceptar;
	afx_msg void OnBnClickedEscsalir();
	afx_msg void OnBnClickedF10aceptar();
	afx_msg void OnEnSetfocusCausa();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnSetfocusCliente();
	afx_msg void OnEnSetfocusFolio();
	afx_msg void OnEnSetfocusNombrecliente();
	CEdit m_tipo;
	CStatic m_tiposeguro;
	afx_msg void OnEnChangeTipo();
};
