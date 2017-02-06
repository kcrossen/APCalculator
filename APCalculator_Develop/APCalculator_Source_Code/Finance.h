#define SolverFinance_TVM \
"NominalInterest = 0.0 /" "*?*/ ; \r\n" \
"NumberOfPeriods = 000 /" "*?*/ ; \r\n" \
"PresentValue = 0.00 /" "*?*/ ; \r\n" \
"FutureValue = 0.00 /" "*?*/ ; \r\n" \
"Payment = 0.00 /" "*?*/ ; \r\n" \
"PeriodsPerYear = 12 /" "*I*/ ; \r\n" \
"PBegin = 0 /" "*I*/ ; \r\n" \
"define tvm() {local i; i=NominalInterest/100/PeriodsPerYear; return PresentValue+(1+(PBegin*i))*Payment*(((1-(1+i)^(-NumberOfPeriods)))/i)+(FutureValue*((1 + i)^(-NumberOfPeriods)));} \r\n" \
"solution_digits = 15; \r\n"

#define SolverFinance_TVM_Odd \
"NominalInterest = 0.0 /" "*?*/ ; \r\n" \
"NumberOfPeriods = 000 /" "*?*/ ; \r\n" \
"FractionOfPeriod = 0.0 /" "*?*/ ; \r\n" \
"PresentValue = 0.00 /" "*?*/ ; \r\n" \
"FutureValue = 0.00 /" "*?*/ ; \r\n" \
"Payment = 0.00 /" "*?*/ ; \r\n" \
"PeriodsPerYear = 12 /" "*I*/ ; \r\n" \
"PBegin = 0 /" "*I*/ ; \r\n" \
"define tvm() {local i; i=NominalInterest/100/PeriodsPerYear; return (PresentValue*((1+i)^FractionOfPeriod))+(1+(PBegin*i))*Payment*(((1-(1+i)^(-NumberOfPeriods)))/i)+(FutureValue*((1 + i)^(-NumberOfPeriods)));} \r\n" \
"solution_digits = 15; \r\n"

#define SolverFinance_Bond_Semiannual_LTE_6mo \
"PriceParValue = 100.00 /" "*?*/ ; \r\n" \
"RedemptionParValue = 100.00 /" "*?*/ ; \r\n" \
"CouponRate = 0.0 /" "*?*/ ; \r\n" \
"NumberOfCoupons = 0 /" "*I?*/ ; \r\n" \
"IssueDate = 2000.0101 /" "*D*/ ; \r\n" \
"SettlementDate = 2000.0101 /" "*D*/ ; \r\n" \
"MaturityDate = 2000.0101 /" "*D*/ ; \r\n" \
"Yield = 0.0 /" "*?*/ ; \r\n" \
"define discnote() \r\n" \
"{local dr, jul_settle, jul_mature; \r\n" \
" dr=DiscountRate/100; \r\n" \
" jul_settle=Jul_DUTCofYMD(int(SettlementDate), int(frac(SettlementDate)*100), int(frac(SettlementDate*100)*100)); \r\n" \
" jul_mature=Jul_DUTCofYMD(int(MaturityDate), int(frac(MaturityDate)*100), int(frac(MaturityDate*100)*100)); \r\n" \
" return (RedemptionParValue-(dr*RedemptionParValue*((jul_mature-jul_settle)/DaysPerYear))-PriceParValue);} \r\n" \
"solution_digits = 15; \r\n"

#define SolverFinance_Advance_Payments \
"NominalInterest = 0.0 /" "*?*/ ; \r\n" \
"NumberOfPayments = 000 /" "*I?*/ ; \r\n" \
"AdvancePayments = 00 /" "*I?*/ ; \r\n" \
"PresentValue = 0.00 /" "*?*/ ; \r\n" \
"FutureValue = 0.00 /" "*?*/ ; \r\n" \
"Payment = 0.00 /" "*?*/ ; \r\n" \
"PaymentsPerYear = 12 /" "*I*/ ; \r\n" \
"define tvm() {local i; i=NominalInterest/100/PaymentsPerYear; return (((PresentValue-(FutureValue*((1 + i)^(-NumberOfPayments))))/(((1-((1+i)^(-(NumberOfPayments-AdvancePayments))))/i)+AdvancePayments))-Payment);} \r\n" \
"solution_digits = 15; \r\n"

#define SolverFinance_Discounted_Notes_Price \
"PriceParValue = 100.00 /" "*?*/ ; \r\n" \
"RedemptionParValue = 100.00 /" "*?*/ ; \r\n" \
"DiscountRate = 0.0 /" "*?*/ ; \r\n" \
"SettlementDate = 2000.0101 /" "*D*/ ; \r\n" \
"MaturityDate = 2000.0101 /" "*D*/ ; \r\n" \
"DaysPerYear = 360 /" "*I*/ ; \r\n" \
"define discnote() \r\n" \
"{local dr, jul_settle, jul_mature; \r\n" \
" dr=DiscountRate/100; \r\n" \
" jul_settle=Jul_DUTCofYMD(int(SettlementDate), int(frac(SettlementDate)*100), int(frac(SettlementDate*100)*100)); \r\n" \
" jul_mature=Jul_DUTCofYMD(int(MaturityDate), int(frac(MaturityDate)*100), int(frac(MaturityDate*100)*100)); \r\n" \
" return (RedemptionParValue-(dr*RedemptionParValue*((jul_mature-jul_settle)/DaysPerYear))-PriceParValue);} \r\n" \
"solution_digits = 15; \r\n"

#define SolverFinance_Discounted_Notes_Yield \
"Yield = 0.0 /" "*?*/ ; \r\n" \
"PriceParValue = 100.00 /" "*?*/ ; \r\n" \
"RedemptionParValue = 100.00 /" "*?*/ ; \r\n" \
"SettlementDate = 2000.0101 /" "*D*/ ; \r\n" \
"MaturityDate = 2000.0101 /" "*D*/ ; \r\n" \
"DaysPerYear = 360 /" "*I*/ ; \r\n" \
"define discnote() \r\n" \
"{local yld, jul_settle, jul_mature; \r\n" \
" yld=Yield/100; \r\n" \
" jul_settle=Jul_DUTCofYMD(int(SettlementDate), int(frac(SettlementDate)*100), int(frac(SettlementDate*100)*100)); \r\n" \
" jul_mature=Jul_DUTCofYMD(int(MaturityDate), int(frac(MaturityDate)*100), int(frac(MaturityDate*100)*100)); \r\n" \
" return ((((RedemptionParValue-PriceParValue)/PriceParValue)*(DaysPerYear/(jul_mature-jul_settle)))-yld);} \r\n" \
"solution_digits = 15; \r\n"

#define SolverDates_Elspsed_Days \
"BeginDate = 2000.0101 /" "*D*/ ; \r\n" \
"EndDate = 2000.0101 /" "*D*/ ; \r\n" \
"ElapsedDays = 0 /" "*?*/ ; \r\n" \
"define days() {local jul_begin, jul_end; \n" \
" jul_begin=Jul_DUTCofYMD(int(BeginDate), int(frac(BeginDate)*100), int(frac(BeginDate*100)*100)); \n" \
" jul_end=Jul_DUTCofYMD(int(EndDate), int(frac(EndDate)*100), int(frac(EndDate*100)*100)); \n" \
" return ((jul_end-jul_begin)-ElapsedDays);} \r\n" \
"solution_digits = 15; \r\n"

#define SolverDates_Add_Days \
"BeginDate = 2000.0101 /" "*D*/ ; \r\n" \
"AddDays = 0 /" "*I*/ ; \r\n" \
"define /" "*D*/ EndDate() {local jul_begin, end_year, end_month, end_day; \n" \
" jul_begin=Jul_DUTCofYMD(int(BeginDate), int(frac(BeginDate)*100), int(frac(BeginDate*100)*100)); \n" \
" Jul_YMDofDUTC((jul_begin+int(AddDays)), `end_year, `end_month, `end_day); \n" \
" return (end_year+(end_month/100)+(end_day/(100*100)));} \r\n" \
"solution_digits = 15; \r\n"

#define SolverFinance_Interest_Rate_Conversion \
"NominalInterest = 0.0 /" "*?*/ ; \r\n" \
"EffectiveInterest = 0.0 /" "*?*/ ; \r\n" \
"PeriodsPerYear = 12 /" "*I*/ ; \r\n" \
"define intconv() {return (100*(((1 + (NominalInterest/100/PeriodsPerYear))^PeriodsPerYear) - 1)) - EffectiveInterest;} \r\n" \
"solution_digits = 15; \r\n"

#define SolverFinance_Interest_Rate_Conversion_Continuous_Compounding \
"NominalInterest = 0.0 /" "*?*/ ; \r\n" \
"EffectiveInterest = 0.0 /" "*?*/ ; \r\n" \
"define intconv() {return (100*((e^(NominalInterest/100)) - 1)) - EffectiveInterest;} \r\n" \
"solution_digits = 15; \r\n"
