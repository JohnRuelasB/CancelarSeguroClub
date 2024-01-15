#ifndef CSTATUSFOLIOCRSEGUROS02
#define CSTATUSFOLIOCRSEGUROS02
#include "stdafx.h"
#include <RecordSet.HPP>
class CStatusFolioCrSeguros02 : public CRecordSet 
{
public:
    CStatusFolioCrSeguros02(C_ODBC *odbc_ext, const char *select=NULL);
    ~CStatusFolioCrSeguros02();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[6];
    int nCTipo[6];
    long nLongitud[6];
    long nLongResp[6];
    void *pVar[6];
    
    long                cliente;
    char                statusseguro[3];
    long                folio;
	short int			claveconyugal;
	SqlTimeStamp        fechavencimiento;
};
#endif CSTATUSFOLIOCRSEGUROS01
