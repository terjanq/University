/*
Edek, kolega Pawła, którego znamy z zadania "Kodowanie", pracuje w kasie banku przyjmując wpłaty i wypłaty z kont klientów. Ponieważ praca ta może być momentami nużąca, Edek wymyślił swój własny system realizowania wpłat i wypłat.

Rozpoczynając swój dzień pracy, Edek ma w kasie kwotę S, z której może realizować wypłaty. Jeżeli do Edka przychodzi klient chcąc wpłacić pieniądze na konto, Edek odnotowuje kwotę wpłaty w systemie, a otrzymane pieniądze (klienci zawsze przynoszą odliczoną kwotę) wkłada do koperty i odkłada na szczyt kupki kopert z wcześniejszymi wpłatami. W sytuacji gdy do Edka przychodzi klient chcąc wypłacić kwotę X, Edek postępuje w następujący sposób: - jeżeli na stosie nie ma żadnej koperty, to pieniądze są wypłacane z kasy - jeżeli kwota do wypłaty X jest mniejsza od najmniejszej kwoty spośród kwot znajdujących się w kopertach, to Edek wypłaca całą kwotę X z kasy - w przeciwnym przypadku, dopóki nie zostanie wypłacona cała kwota, Edek zdejmuje kolejno koperty ze szczytu kupki i wypłaca brakującą kwotę. Jeżeli na końcu, po wydaniu całej kwoty, w ostatnio zdjętej kopercie pozostały jakieś pieniądze, to są one wkładane do kasy. Jeżeli zdarzy się, że Edek zdejmie z kupki wszystkie koperty, a klient nie otrzymał całej kwoty, to pozostałą część pieniędzy Edek wydaje z kasy. Możesz założyć, że w kasie zawsze znajduje się wystarczająco dużo pieniędzy, aby dokonać koniecznych operacji. Ponieważ jest to system bankowy, Edek nie chciałby popełnić błędu. Z tego powodu Edek poprosił Ciebie o napisanie programu, który pomoże mu obliczyć jaka kwota powinna znajdować się w kasie, a jaka w kopertach, które pozostały na kupce, po wykonaniu wszystkich wpłat i wypłat klientów.
Wejście
W pierwszej linii wejścia znajduje się pojedyncza liczba T (1<=T<=3) oznaczająca liczbę zastawów danych. W kolejnych liniach wejścia znajdują się opisy zestawów danych. Pojedynczy zestaw danych zawiera zapis wszystkich akcji klientów banku. W pierwszej linii takiego opisu znajdują się dwie liczby całkowite n (1<=n<=10^6) i S (1<=S<=10^12). Oznaczają one odpowiednio ilość akcji klientów banku oraz początkową kwotę jaka znajdowała się w kasie na początku dnia. W kolejnych n liniach opisu zestawu danych znajdują się opisy pojedynczych akcji klientów. Opis akcji składa się z jednej liczby całkowitej x (-10^6<=x<=10^6, x jest różne od zera). Kwota dodatnia oznacza wpłatę na konto, kwota ujemna oznacza wypłatę pieniędzy z konta. Możesz założyć, że podczas realizowania kolejnych akcji klientów, w kasie nigdy nie znajdzie się kwota większa niż 10^12.

Wyjście
Dla każdego zestawu danych należy wypisać jedną linię zawierającą dwie liczby całkowite oddzielone pojedynczym odstępem. Są to odpowiednio kwota jaka pozostała w kasie po zrealizowaniu wszystkich akcji klientów banku oraz sumaryczna kwota znajdującą się w kopertach, które pozostały na kupce.

Przykład
Dla danych wejściowych

2
6 1000
100
70
400
-50
-100
-200
3 100
10
50
-20
poprawną odpowiedzią jest
1220 0
130 10
*/

#include <iostream>
#include <cstdio>
#include <stack>



using namespace std;

int main(){
	int T, n, a;

	scanf("%d", &T);

	while(T--){
		stack <int> mins;
		stack <int> cash;
		long long summary = 0;
		long long S = 0;
		scanf("%d %lld", &n, &S);

		while( n-- ){
			scanf("%d", &a);
			if( a > 0 ){
				cash.push( a );
				summary += a;

				if( mins.empty() || a <= mins.top() )
					mins.push( a );
			}
			else{
				if( cash.empty() || 0 < a + mins.top() ){
					S += a;
				}
				else{
					while( !cash.empty() && a < 0 ){
						int top = cash.top();
						cash.pop();
						summary -= top;

						if( mins.top() == top ) mins.pop();
						a += top;
					}

					S += a;
				}
			}

		}

		printf("%lld %lld\n", S, summary);
	}









	return 0;
}