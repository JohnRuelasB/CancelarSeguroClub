#define MAIN

#include "CancelarSeguroClub.h"
#include "DlgCancelarSeguroClub.h"
#include "sysCancelarSeguroClub.hpp"
#include "password.hpp"
#include "gnwproto.hpp"
#include "wtienda.hpp"
#include "CargarDLL.h"

#include "strsafe.h"

void memcopy(void *dest, void *src, size_t n){
	    char *csrc = (char*)src;
        char *cdest = (char*)dest;
        for(unsigned int i=0; i<n; i++)
                cdest[i] = csrc[i];
}


int CN0027( char *cInput1, char *cInput2, char *cOutPut1, char *cOutPut2 )
{
	HRESULT hr = 0;
	UNREFERENCED_PARAMETER( cInput2 );
	UNREFERENCED_PARAMETER( cOutPut2 );
	
    int nRegresa = 0;
	char cIpTiendaLocal[30] = {0};
	char cIPServidorCartera[25]={0}, cIPServidorCarteraAlterno[25]={0}, cSql[255]={0};
	CString sTexto;
	char cMensajeOut[MAX_BUFFER_XML] = {0};

    SParametros parametros;

    SecureZeroMemory( &parametros, sizeof( SParametros ) );
	
    memcopy( &parametros, cInput1, sizeof( SParametros ) );

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
		//to do sprintf(cIpTiendaLocal,"%s",dlg.sServer);
		hr = StringCchPrintf(cIpTiendaLocal,size_t(cIpTiendaLocal),TEXT("%s"),dlg.sServer);

		//if ( abrirConexion(cIpTiendaLocal,cIpTiendaLocal,dlg.iTienda) == true )
		if ( abrirConexionBD( &odbcTiendaNumero, 0, cIpTiendaLocal, cIpTiendaLocal, CONECTA_TIENDANUMERO, dlg.iTienda ) )
		{
			//if ( abrirConexionCartera(&odbc) == true )
			if ( consultarIpServidores( &odbcTiendaNumero, cIPServidorCartera, cIPServidorCarteraAlterno, SERV_CARTERA, cSql ) )			
			{
				if ( abrirConexionBD( &odbcCartera, SERV_CARTERA, cIPServidorCartera, cIPServidorCarteraAlterno, CONECTA_CARTERA, parametros.iTienda ) )
				{
					//to do sprintf(dlg.cIpServidorCartera,"%s",cIPServidorCartera);
					hr = StringCchPrintf(dlg.cIpServidorCartera,size_t(dlg.cIpServidorCartera),TEXT("%s"),cIPServidorCartera);
					dlg.DoModal();
					//to do sprintf( cOutPut1,"%d",dlg.iAllOk );
					hr = StringCchPrintf(cOutPut1,size_t(cOutPut1),TEXT("%d"),dlg.iAllOk);
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