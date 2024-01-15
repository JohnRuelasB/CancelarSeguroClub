#include "CCONSULTARMENSAJESEGURO.HPP"
CConsultarMensajeSeguro::CConsultarMensajeSeguro(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
 
    nLongitud[0] = 1026;
    pVar[0] =  des_mensaje;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarMensajeSeguro::~CConsultarMensajeSeguro()
{
}
    
void CConsultarMensajeSeguro::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
