#include "CINSTEMCACARMOVADICS.HPP"
CInsTemCaCarmovAdics::CInsTemCaCarmovAdics(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=17;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_CHAR;
    nSqlTipo[8] = SQL_CHAR;
    nSqlTipo[9] = SQL_SMALLINT;
    nSqlTipo[10] = SQL_INTEGER;
    nSqlTipo[11] = SQL_VARCHAR;
    nSqlTipo[12] = SQL_INTEGER;
    nSqlTipo[13] = SQL_CHAR;
    nSqlTipo[14] = SQL_INTEGER;
	nSqlTipo[15] = SQL_CHAR;
	nSqlTipo[16] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_SSHORT;
    nCTipo[10] = SQL_C_SLONG;
    nCTipo[11] = SQL_C_CHAR;
    nCTipo[12] = SQL_C_SLONG;
    nCTipo[13] = SQL_C_CHAR;
    nCTipo[14] = SQL_C_SLONG;
	nCTipo[15] = SQL_C_CHAR;
	nCTipo[16] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    nLongitud[9] = 3;
    nLongitud[10] = 5;
    nLongitud[11] = 107;
    nLongitud[12] = 5;
    nLongitud[13] = 17;
    nLongitud[14] = 5;
	nLongitud[15] = 3;
	nLongitud[16] = 3;
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] = &tienda;
    pVar[3] = &ciudad;
    pVar[4] = &cliente;
    pVar[5] = &caja;
    pVar[6] = &causabaja;
    pVar[7] =  movtoseguro;
    pVar[8] =  statusseguro;
    pVar[9] = &edad;
    pVar[10] = &folio;
    pVar[11] = &fecha;
    pVar[12] = &efectuo;
    pVar[13] =  ipcarteracliente;
    pVar[14] = &bonificacion;
	pVar[15] =  tiposeguro;
	pVar[16] =  flagseguroconyugal;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CInsTemCaCarmovAdics::~CInsTemCaCarmovAdics()
{
    Commit();
}
    
void CInsTemCaCarmovAdics::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CInsTemCaCarmovAdics::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("caCarmov");
    return (retorno);
}
BOOL CInsTemCaCarmovAdics::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, tienda, ciudad, cliente, caja, causabaja, movtoseguro, statusseguro, edad, folio, fecha, efectuo, ipcarteracliente, bonificacion, tiposeguro, flagseguroconyugal ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
