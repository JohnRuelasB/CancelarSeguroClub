#include "CSTATUSFOLIOCRSEGUROS02.HPP"
CStatusFolioCrSeguros02::CStatusFolioCrSeguros02(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=5;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
	nSqlTipo[3] = SQL_SMALLINT;
	nSqlTipo[4] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
	nCTipo[3] = SQL_C_SSHORT;
	nCTipo[4] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 3;
    nLongitud[2] = 5;
	nLongitud[3] = 3;
	nLongitud[4] = 107;
    pVar[0] = &cliente;
    pVar[1] =  statusseguro;
    pVar[2] = &folio;
	pVar[3] = &claveconyugal;
	pVar[4] = &fechavencimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CStatusFolioCrSeguros02::~CStatusFolioCrSeguros02()
{
    Commit();
}
    
void CStatusFolioCrSeguros02::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CStatusFolioCrSeguros02::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crSeguros");
    return (retorno);
}
BOOL CStatusFolioCrSeguros02::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, statusseguro, folio, claveconyugal, fechavencimiento) VALUES (?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
