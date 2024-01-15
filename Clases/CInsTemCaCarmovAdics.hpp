#ifndef CINSTEMCACARMOVADICS
#define CINSTEMCACARMOVADICS
#include "stdafx.h"
#include <RecordSet.HPP>
class CInsTemCaCarmovAdics : public CRecordSet 
{
public:
    CInsTemCaCarmovAdics(C_ODBC *odbc_ext, const char *select=NULL);
    ~CInsTemCaCarmovAdics();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[18];
    int nCTipo[18];
    long nLongitud[18];
    long nLongResp[18];
    void *pVar[18];
    
    char                clave[3];
    char                tipomovimiento[3];
    short int           tienda;
    short int           ciudad;
    long                cliente;
    short int           caja;
    short int           causabaja;
    char                movtoseguro[3];
    char                statusseguro[3];
    short int           edad;
    long                folio;
    SqlTimeStamp        fecha;
    long                efectuo;
    char                ipcarteracliente[17];
    long                bonificacion;
	char				tiposeguro[3];
	char				flagseguroconyugal[3];
};
#endif CINSTEMCACARMOVADICS
