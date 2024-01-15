#define MAIN

#include "CancelarSeguroClub.h"
#include "DlgCancelarSeguroClub.h"
#include "sysCancelarSeguroClub.hpp"
#include "password.hpp"
#include "gnwproto.hpp"
#include "wtienda.hpp"
#include "CargarDLL.h"

int CN0027( char *cInput1, char *cInput2, char *cOutPut1, char *cOutPut2 )
{
	UNREFERENCED_PARAMETER( cInput2 );
	UNREFERENCED_PARAMETER( cOutPut2 );
	
    int nRegresa = 0;
	char cIpTiendaLocal[30] = {0};
	char cIPServidorCartera[25]={0}, cIPServidorCarteraAlterno[25]={0}, cSql[255]={0};
	CString sTexto;
	char cMensajeOut[MAX_BUFFER_XML] = {0};

    SParametros parametros;

    memset( &parametros, 0, sizeof( SParametros ) );

    memcpy( &parametros, cInput1, sizeof( SParametros ) );

    if ( checarLink( parametros.iLink ) )
    {	
		CDlgCancelarSeguroClub dlg;

		dlg.sServer.Format( "%s", parametros.sServer );
		dlg.iTienda = parametros.iTienda;
		dlg.lEmpleado = parametros.lEmpleado;
		dlg.iCaja = parametros.iCajaActual;
		dlg.iMuestraMsg = parametros.iMuestraMsg;
		dlg.lCliente = parametros.lCliente;
		dlg.iSistema = parametros.iNumSistema;
		dlg.lFolio = parametros.lFolioSeguro;
		dlg.iTipo = parametros.iTipo;		        
		sprintf(cIpTiendaLocal,"%s",dlg.sServer);

		//if ( abrirConexion(cIpTiendaLocal,cIpTiendaLocal,dlg.iTienda) == true )
		if ( abrirConexionBD( &odbcTiendaNumero, 0, cIpTiendaLocal, cIpTiendaLocal, CONECTA_TIENDANUMERO, dlg.iTienda ) )
		{
			//if ( abrirConexionCartera(&odbc) == true )
			if ( consultarIpServidores( &odbcTiendaNumero, cIPServidorCartera, cIPServidorCarteraAlterno, SERV_CARTERA, cSql ) )			
			{
				if ( abrirConexionBD( &odbcCartera, SERV_CARTERA, cIPServidorCartera, cIPServidorCarteraAlterno, CONECTA_CARTERA, parametros.iTienda ) )
				{
					sprintf(dlg.cIpServidorCartera,"%s",cIPServidorCartera);
					dlg.DoModal();
					sprintf( cOutPut1,"%d",dlg.iAllOk );
					nRegresa=1;
				}
				else
				{
					AfxMessageBox("Error al intentar conectarse a Cartera");//Error al intentar conectarse a Cartera
				}
			}
		}
		else
		{
			AfxMessageBox("No se pudo realizar la conexion");//No se pudo realizar la conexion
		}

		cerrarConexionBD(&odbcTiendaNumero);
		cerrarConexionBD(&odbcCartera);
	}

	return nRegresa;

}