#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
using namespace std;

#define MAX 1000

string location[5][5] =
{
    {"Ghaziabad", "Sahibabad", "Anand Vihar", "Loni", "Sanjay Nagar"},
    {"Mohan Nagar", "Vasundhara", "Vaishali", "Kaushambhi", "Delhi"       },
    {"Shakti Khand", "Shipra", "Niti Khand", "Gyan Khand", "Ghazipur"    },
    {"Lal Kuan", "Noida", "Gautam Budh", "Raj Nagar", "Dasna"       },
    {"Haryana", "Greater Noida", "Dadri", "Sikandrabad", "Bulandshahr" }
};

void vline(char ch)
{
    for (int i = 105; i > 0; i--)
        cout << ch;
}

void show_map()
{
    cout<<endl<<"\t\t\t\t\t\t\t\t\t\t\t\tMap of the locations"<<endl<<endl;
    cout<<"\t\t\t\t\t\t  ";
    vline('*');
    cout<<endl;
    for(int i = 0; i < 5; i++)
    {
        cout<<"\t\t\t\t\t\t";
        for(int j = 0; j < 5; j++)
        {
            cout.width(5);
            cout << i*5 + j << ".";
            cout.width(15);
            cout << location[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"\t\t\t\t\t\t  ";
    vline('*');
    cout<<endl;
}

int partition(int * time, int * dest, string * person, int start, int end)
{

    int pivot = time[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (time[i] <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    swap(time[pivotIndex], time[start]);
    swap(dest[pivotIndex], dest[start]);
    swap(person[pivotIndex], person[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (time[i] <= pivot)
        {
            i++;
        }

        while (time[j] > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(dest[i], dest[j]);
            swap(person[i], person[j]);
            swap(time[i++], time[j--]);
        }
    }

    return pivotIndex;
}

void sort_time(int * time, int * dest, string * person, int start = 0, int end = 20-1)
{

    if (start >= end)
        return;

    int p = partition(time, dest, person, start, end);

    sort_time(time, dest, person, start, p - 1);
    sort_time(time, dest, person, p + 1, end);
}

void find_shortest_dest(vector<vector<int>> &gmap, vector<vector<bool>> visited, int row, int col, int &mrow, int &mcol,int &mini, int k = 0)
{

    if(gmap[row][col] > 0)
    {

//        cout<<row<<" "<<col<<" "<<k<<endl;
        if(k < mini)
        {
//            --gmap[row][col];
//            --countt;
            mini = k;
            mrow = row;
            mcol = col;
        }
        return;
    }
//    cout<<"hi";
    if(visited[row][col] == false)
    {
        return;
    }
    visited[row][col] = false;

    if(row < gmap.size() - 1)
    {
        find_shortest_dest(gmap, visited, row+1, col, mrow, mcol, mini, k+1);
    }
    if(col < gmap[0].size() - 1)
    {
        find_shortest_dest(gmap, visited, row, col+1, mrow, mcol, mini, k+1);
    }
    if(col > 0 )
    {
        find_shortest_dest(gmap, visited, row, col-1, mrow, mcol, mini, k+1);
    }
    if(row > 0 )
    {
        find_shortest_dest(gmap, visited, row-1, col, mrow, mcol, mini, k+1);
    }

    visited[row][col] = true;
}

void route_cab1(vector<vector<int>> gmap, int dest[], int si, int sj, int countt)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(j > 2)
            {
                gmap[i][j] = 0;
            }
        }
    }

    int i = si, j = sj;
    int mi = 0, mj = 0;
    while(countt--)
    {
        vector<vector<bool>> visited
        {
            {true,true,true,true,true},
            {true,true,true,true,true},
            {true,true,true,true,true},
            {true,true,true,true,true},
            {true,true,true,true,true}
        };
        int min_dist = INT_MAX;
        find_shortest_dest(gmap, visited, i, j, mi, mj, min_dist);
        cout<<"Cab 1 will go from "<<location[i][j]<<"("<<i<<","<<j<<") to "<<location[mi][mj]<<"("<<mi<<","<<mj<<") ";
        cout<<"and will cover "<<abs(i - mi) + abs(j - mj)<<" distance"<<endl;
        --gmap[mi][mj];
        i = mi;
        j = mj;
    }

}

void route_cab2(vector<vector<int>> gmap, int dest[], int si, int sj, int countt)
{
    for(int i = 0; i < gmap.size(); i++)
    {
        for(int j = 0; j < gmap[0].size(); j++)
        {
            if(j <= 2)
            {
                gmap[i][j] = 0;
            }
        }
    }

    int i = si, j = sj;
    int mi = 0, mj = 0;
    while(countt--)
    {
        vector<vector<bool>> visited
        {
            {true,true,true,true,true},
            {true,true,true,true,true},
            {true,true,true,true,true},
            {true,true,true,true,true},
            {true,true,true,true,true}
        };
        int min_dist = INT_MAX;
        find_shortest_dest(gmap, visited, i, j, mi, mj, min_dist);
        cout<<"Cab 2 will go from "<<location[i][j]<<"("<<i<<","<<j<<") to "<<location[mi][mj]<<"("<<mi<<","<<mj<<") ";
        cout<<"and will cover "<<abs(i - mi) + abs(j - mj)<<" distance"<<endl;
        --gmap[mi][mj];
        i = mi;
        j = mj;
    }

}

int countMinCoins(int n, int C[], int m, int dp[])
{
	if (n == 0) {
		dp[0] = 0;
		return 0;
	}

	if (dp[n] != -1)
		return dp[n];

	int ret = INT_MAX;

	for (int i = 0; i < m; i++) {

		if (C[i] <= n) {

			int x = countMinCoins(n - C[i],C, m,dp);

			if (x != INT_MAX)
				ret = min(ret, 1 + x);
		}
	}

	dp[n] = ret;
	return ret;
}

void den_comb(int n, int C[], int m, vector <int> &denomination,int dp[])
{

	if (n == 0) {

		for (auto it : denomination) {
			cout << it << ' ';
		}

		return;
	}

	for (int i = 0; i < m; i++) {

		if (n - C[i] >= 0 && dp[n - C[i]] + 1 == dp[n]) {
			denomination.push_back(C[i]);

			den_comb(n - C[i], C, m,denomination,dp);
			break;
		}
	}
}

void count_den(int X, int C[],int N)
{

    int dp[MAX+1];
    for(int i=0;i<MAX;i++)
    {
        dp[i]=-1;
    }
	int isPossible = countMinCoins(X,C,N,dp);

	if (isPossible == INT_MAX) {
		cout << "-1";
	}

	else {
            cout<<isPossible<<" and possible denominations are ";
            vector<int> denomination;
		den_comb(X, C, N,denomination,dp);
	}
}

void cost(string person[], int dest[], int st, int en, int si, int sj)
{
    int coins[] = {500,200,100,50,20,10};
    int m = sizeof(coins)/sizeof(coins[0]);
    for(int i = st; i <= en; i++)
    {
        int ii = dest[i]/5;
        int jj = dest[i]%5;
        int price = 50*(abs(ii - si) + abs(jj - sj));
        cout<<person[i]<<" deboarding "<<location[ii][jj]<<"("<<ii<<","<<jj<<")"<<" have to pay Rs."<<price<<" and minimum notes required is ";
        count_den(price, coins, m);
        cout<<endl;
    }
}

void dest_grouping(vector<vector<int>> gmap, string person[], int time[], int dest[], int st, int en)
{
    int si = 3, sj = 1;
    int cab1[4], cab2[4];
    int c1 = 0, c2 = 0;

    for(int i = st; i <= en; i++)
    {
//        int j = dest[i] - ((dest[i]/5)*5);
        if(dest[i] % 5 <= 2)
        {
            cab1[c1++] = dest[i];
        }
        else
        {
            cab2[c2++] = dest[i];
        }
    }

    cost(person, dest, st, en, si, sj);
    cout<<endl;

    cout<<"Cab 1 will be serving in the areas : "<<endl;
    for(int i = 0; i < c1; i++)
    {
        cout.width(5);
        cout<<cab1[i];
        cout<<". "<<location[cab1[i]/5][cab1[i]%5]<<endl;
    }
    cout<<endl<<"Cab 2 will be serving in the areas : "<<endl;
    for(int i = 0; i < c2; i++)
    {
        cout.width(5);
        cout<<cab2[i];
        cout<<". "<<location[cab2[i]/5][cab2[i]%5]<<endl;
    }
    cout<<endl<<endl;

    if(c1 > 0)
    {
        cout<<"The Path of cab1 will be : "<<endl;
        route_cab1(gmap, dest, si, sj, c1);
    }
    if(c2 > 0)
    {
        cout<<endl<<"The Path of cab2 will be : "<<endl;
        route_cab2(gmap, dest, si, sj, c2);
    }
}

void time_grouping(string person[], int time[], int dest[])
{
    int i = 0;
    int start_time = 0;
    int round = 1;
//    int gmap[5][5];
    vector<vector<int>> gmap;
    for(int i = 0; i < 5; i++)
    {
        vector<int> im;
        for(int j = 0; j < 5; j++)
        {
            im.push_back(0);
        }
        gmap.push_back(im);
    }
    int st_no = 0;    // starting number for the next round
    while(i < 20)
    {
        st_no = i;

        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                gmap[i][j] = 0;
            }
        }
        int lati = 0, longi = 0;
        start_time = time[i];
        cout<<endl;
        system("pause");
        system("cls");
        show_map();
        cout<<endl<<endl<<"\t\t\tRound "<<round++<<" is starting at "<<start_time/100<<":"<<start_time%100<<endl<<endl;

        while(time[i] < start_time+30 && i < 20)
        {
            lati = dest[i]/5;
            longi = dest[i] - ((dest[i]/5)*5);
            ++gmap[lati][longi];
            ++i;
        }

        dest_grouping(gmap, person, time, dest, st_no, i-1);

    }
}

int main()
{
    system(" color 0F");
    printf("\t\t\t\t\t\t\t\t\t                      .:. :!~?!!!Y!^J^J^J77.~:..                      \n");
    printf("\t\t\t\t\t\t\t\t\t                   .^~:?J~  ?~?!?~! .7^7~?!?^5JJ7.~^                   \n");
    printf("\t\t\t\t\t\t\t\t\t               .:  !7^J^7...^^^:^^^?~^^^^::^^^!7~?Y7 ?~.               \n");
    printf("\t\t\t\t\t\t\t\t\t             ::J7^. ^~~:^^~~~~~~~!YYY7~~~~~~~~^^^.^:!!^?~^:            \n");
    printf("\t\t\t\t\t\t\t\t\t          .:~J^^?!^:^^~~~~~~~~~~JPYJYGJ!~~~~~~~~~~^^^.~!J^?~.          \n");
    printf("\t\t\t\t\t\t\t\t\t         :^!!.~::^~~~~~~~~~~~~^?5PJJJ5YY?~~~~~~~~~~~~~^:~~!7Y^:        \n");
    printf("\t\t\t\t\t\t\t\t\t       :7^!!?::^~~~~~~~~~~~~~!JYJY5JJYPJYY7~~~~~~~~~~~~~^::~Y~. .      \n");
    printf("\t\t\t\t\t\t\t\t\t      ^7~!^.:^~~~~~~~~~~~~~~?YYJJJPJJJPJJPJJ!~~~~~~~~~~~~~^:. .~?^     \n");
    printf("\t\t\t\t\t\t\t\t\t    .7~~!:.^~~~~~~~~~~~~~~~YYJJJJJPYJJPJJPJJY!~~~~~~~~~~~~~~^.^~~?!.   \n");
    printf("\t\t\t\t\t\t\t\t\t    ~~~~.:~~~~~~~~~~~~~~~~?5JJJJJJPJJY5JJPJJY?~~~~~~~~~~~~~~~~.!7!~^   \n");
    printf("\t\t\t\t\t\t\t\t\t   !7!7.:~~~~~~~~~~~~~~~~~75JJJJJYPJYPYJ55JJJ?~~~~~~~~~~~~~~~~~.:7~~!  \n");
    printf("\t\t\t\t\t\t\t\t\t  .!!!~.~~~~~~~~~~~~~~~~~~~J5YYYYYYY5YYYYYYY5!~~~~~~~~~~~~~~~~~~.!~:!: \n");
    printf("\t\t\t\t\t\t\t\t\t .!JJ! ^~~~~~~~~~~~~~~~~~~~~5YYYYYYYYYYYYYYYJ~~~~~~~~~~~~~~~~~~~^ ~7J^.\n");
    printf("\t\t\t\t\t\t\t\t\t :!77:.~~~~~~~~~~~~~~~~~~~~^~JY????????????!^~~~~~~~~~~~~~~~~~~~~.:77?:\n");
    printf("\t\t\t\t\t\t\t\t\t :..: ^~~~~~~~~~~~~~~~~~~:^~^7Y??77777777?7^~^:~~~~~~~~~~~~~~~~~~^ !Y?^\n");
    printf("\t\t\t\t\t\t\t\t\t J?!?.^~~~~~~~~~~~~~~~~^^7~^!!~~YJJJJJJJ7!!!^~7^^~~~~~~~~~~~~~~~~^ ~7!~\n");
    printf("\t\t\t\t\t\t\t\t\t ~~~! ^~~~~~~~~~~~~~~~^^J7~JJJ^7YYJJJ?YY7~JJJ~7J^^~~~~~~~~~~~~~~~^ 7~^J\n");
    printf("\t\t\t\t\t\t\t\t\t ??7? ^~~~~~~~~~~~~~~~:?J^?JJ?^JJJ???7JJ?^JJJ?^J?:~~~~~~~~~~~~~~~^ !77~\n");
    printf("\t\t\t\t\t\t\t\t\t ~?!. :~~~~~~~~~~~~~~^~J?^JJJ7~JJYJ?J?JJJ^?JJJ^?J~^~~~~~~~~~~~~~~:.7:..\n");
    printf("\t\t\t\t\t\t\t\t\t ~?7~:.~~~~~~~~~~~~~~^~J?^JJJ7~JJYJJJ?YJJ^?JJJ^?J~^~~~~~~~~~~~~~~.!!~?.\n");
    printf("\t\t\t\t\t\t\t\t\t  ~?!~.:~~~~~~~~~~~~~^^J?^?JJ?^JJYYJJJYJ?^JJJ?^JJ^^~~~~~~~~~~~~~: ~7~!.\n");
    printf("\t\t\t\t\t\t\t\t\t  :~~J^ ^~~~~~~~~~~~~~:~J!!JJJ^??JYJYYY?!~JJJ~!J~:~~~~~~~~~~~~~^ ?7!?  \n");
    printf("\t\t\t\t\t\t\t\t\t   ^77?~.^~~~~~~~~~~~~~:~J~!7!^^77YYYYY7:!!7~^?~:~~~~~~~~~~~~~^.:~~~~  \n");
    printf("\t\t\t\t\t\t\t\t\t    .!~!~ :~~~~~~~~~~~~~^^^~~?J~7JYYY55!!J?~~^:^~~~~~~~~~~~~~: .~?7^   \n");
    printf("\t\t\t\t\t\t\t\t\t           .^~~~~~~~~~~~~~^^^^~7~7J55P5!7~^^^^~~~~~~~~~~~~~^.    :^    \n");
    printf("\t\t\t\t\t\t\t\t\t             :~~~~~~~~~~~~~~~^::^:^????^::^~~~~~~~~~~~~~~~:            \n");
    printf("\t\t\t\t\t\t\t\t\t              .:^~~~~~~~~~~~~~~~^~!!!!7!~~~~~~~~~~~~~~~^:.             \n");
    printf("\t\t\t\t\t\t\t\t\t                 .^?YYYJ!~~~7JYYJ?!~~~~?JYJ?!~~~~~~~Y5:                \n");
    printf("\t\t\t\t\t\t\t\t\t                  JGGGGGP7~?GGGGGGJ~!!YGGGGGP7~~~^:.5G:                \n");
    printf("\t\t\t\t\t\t\t\t\t                  JGGGGGP~:?GGGGGGJ~~~YGGGGGG!..   ?GP.                \n");
    printf("\t\t\t\t\t\t\t\t\t                   ~?J?7!~  ^?JJ?!?:..:!JYJ?!! ^~?5GGP~:^^::.          \n");
    printf("\t\t\t\t\t\t\t\t\t                    .!!JP!    ~!75Y     .!7?P?.Y5PGGGGYYYYYY!          \n");
    printf("\t\t\t\t\t\t\t\t\t                    ~GGGG!   .PGGGY     ^GGGG?   JGGGP:                \n");
    printf("\t\t\t\t\t\t\t\t\t                :^: ^GGGG7   .5GGGY     ^GGGG?   ?GGGP: :^^.           \n");
    printf("\t\t\t\t\t\t\t\t\t               7PGG?^GGGG7   .5GGG5     ^GGGG?   ?GGGP.~GGGP^          \n");
    printf("\t\t\t\t\t\t\t\t\t               !PGP~~GGGY:   .5GGG5     ^GGGG?   :YPGG7~5GPY:          \n");
    printf("\t\t\t\t\t\t\t\t\t                :~!~7?7^      ^^^^:     .^^^^:     :~!!~^^:  \n\n\n\n");
    printf("\t\t\t\t                                         ..                                               ....                                     ...                         \n");
    printf("\t\t\t\t             ~5        :~YPY77?Y?^    ~Y?!!7?J?        :~5PY77?Y?:  :~YP5?77JY!.       ~J?7!77J?:     .^7PP?^.:!5PJ77777J5.    :7J?7!!7??5. YY777YPY777YY       \n");
    printf("\t\t\t\t            ^#@5         5@5   ~&@Y  ?@!    .55          5@5  .~&@J   Y@P   :P@B:    ^G#!     .?&5:     :@@~    B@?      J:   J&5:     .7#:.J.   5@Y   .J.      \n");
    printf("\t\t\t\t           ^G~G@J        Y@5    5@&. J@B7:    !          Y@Y    5@&.  J@5    7@@~   ~@@~        J@B.    :&@^    G@7     :    P@P         ~:      5@Y            \n");
    printf("\t\t\t\t          :G~ .B@?       Y@P::^?&#7   7G@&GJ~.           Y@5::^J&#!   J@P:^~JGP!    P@#         ^@@?    :&@^    G@Y~!!!55   !@@!                 5@Y            \n");
    printf("\t\t\t\t         .BJ^^^7@@!      Y@P^~!7^.      :!5#@#J.         Y@P^~!7^.    J@G^?&@!      P@#.        ^@@7    :&@^    G@J.:::!J   !@@~                 5@Y            \n");
    printf("\t\t\t\t         P?^^^^^!&@~     Y@5         !.     ~B@Y         Y@Y          J@5  :P@Y.    ~@@!        J@B.    :&@^    G@7       ...B@5          .      5@Y            \n");
    printf("\t\t\t\t       .PJ       !@&~    5@P         YP:     Y@7         5@5          Y@P    7&#7.   ~B&7.    .?&5. .JJ.:@G     B@?     .!Y. :5@P^.    .^7:      5@5            \n");
    printf("\t\t\t\t      ^JP7^     :!5P5!::~YP5~:       7J?7!!7JJ^        :~5PY~:      :~YP5~:   :5PJ!:   ~JJ7!77J?:   .5#Y7?.   ^!5PY77777J5:    ^J5YJ?77!^      :~5PY~:          \n");
    printf("\t\t\t\t                                          ...                                              ...          .                           ...                     \n");
    system("pause");
    cout<<"Press any key to continue.....";
    system("cls");
    printf("\t\t\t\t                                          .7!~~~!!!~~!7^    .~!!!77!:    .^!!!!~!!^   .^~!!!^.    .~77!!!~^!.                                                   \n");
    printf("\t\t\t\t                                          ~P^::^&@!::^YJ  .JB?^...:7G5^    ?@&^:^?##7  .~@@!    :5B?^...:~Y@:                                                   \n");
    printf("\t\t\t\t                                          ..   .#@^    : ^#@!       :&@7   ~@#    7@@~  :&@:   !&&^        ?~   ..                                              \n");
    printf("\t\t\t\t                                               .#@~      G@G         J@&:  ~@#.  .5@B:  :&@^  .#@J             !&P                                              \n");
    printf("\t\t\t\t                                               .#@~     .#@5         7@@^  ~@#!!7Y57.   :&@^  ~@@7             .^:                                              \n");
    printf("\t\t\t\t                                               .#@^      5@B         Y@B.  ~@#.         :&@^  .#@Y                                                              \n");
    printf("\t\t\t\t                                               .&@^      .P@Y       ~@B^   ~@#          :&@:   ~#@7        ~^   ..                                              \n");
    printf("\t\t\t\t                                              :!&@?:.      !P5!^^^!JP7   .:J@&~:       :7&&7:.  .JBPJ!~~~!7^   7&P                                              \n");
    printf("\t\t\t\t                                              ::::::.        .^~~~^:     .::::::       ::::::.     :~!!~^.     .^:                                              \n");
    printf("\t\t\t\t                                                                                                                                                                \n");
    printf("\t\t\t\t                                                                                                                                                                \n");
    printf("\t\t\t\t                                                                                                                                                                \n");
    printf("\t\t\t\t        ....                                                               ....            ....                                                     ....        \n");
    printf("\t\t\t\t     !JJ7!!77?P~        ?5        :!PGY777?YJ~         :^YGP77?YJ~     .7J?!!7?Y7.      :7J7!!7?Y7.   :~YGP!^.      .^?GG?^^!JPP~      :!PJ^.   .7Y?7!!!7?5^    \n");
    printf("\t\t\t\t   !#B~      ^B?       !&@J         G@?    :5@P.         7@B   :G@P.  ?&P:     :P&?    J&5.     ^G#7    J@G           ^@@:    J@@5:      B!    ?&5:      ^G?    \n");
    printf("\t\t\t\t  7@&:        .~      ~G^B@?        P@?     !@@^         !@B    ?@@^ Y@B        .#@J  5@G        .&@?   ?@G           ^@&:    ?P7&@J.    G~   5@5          :    \n");
    printf("\t\t\t\t  B@P                ^G: :#@!       P@5~~!75&G~          !@B::^7#&? :&@J         Y@&.^@@?         P@#.  ?@G           ^@&:    ?5 .Y@#!   G~  !@@~      :~777~.  \n");
    printf("\t\t\t\t .#@P               :#?^^^?@&~      P@Y::^~?G#5^         !@B~~!7~.  :&@Y         Y@&.:@@?         5@#.  ?@G           ^@&:    ?5   ^P@P^ G~  !@@!       .G@P    \n");
    printf("\t\t\t\t  ?@&:         .   .G7^^^^^7@#:     P@?      B@B         !@B         Y@#.        B@?  5@B        .#@7   ?@G        :  ^@&:    ?5     !#@JB~  .G@B.       5@Y    \n");
    printf("\t\t\t\t   ?&#7.     :!~  :G7       J@#:    G@?    .7&@?         7@#          ?&G^     ^P#7    J&P:     ^G#!    J@B      ^Y^  ^@@:    JP       ?&@~   .Y&B!.     P@5    \n");
    printf("\t\t\t\t     .755Y??77~.  ~YP!:     :7PPY~.:!5PY777?JY7:        :^JPP!^         .7J?7!7?J!.      .7J?7!7?J!    :~YP5?7777?57 .^?PP7^.:~Y5~:      :5^     :7YY?7!7?YJ^   \n");
    printf("\t\t\t\t         ...                                                                ...              ...                                                     ....       \n");
    system("pause");
    cout<<"\n\n\n\nPress any key to continue.....";
    system("cls");
    show_map();

    string person[20];
    int time[20];
    int dest[20];

    for(int i = 0; i < 20; i++)
    {
        cout<<"Enter the name of the person "<<i+1<<" : ";
        cin>>person[i];
        cout<<"Enter the time of the student "<<i+1<<" : ";
        cin>>time[i];
        while(time[i] < 1500)
        {
            system(" color 4F");
            cout<<endl<<"Services not started. Please enter again : ";
            cin>>time[i];
            system(" color 0F");
        }
        while(time[i] > 1800)
        {
            system(" color 4F");
            cout<<endl<<"Services ended. Please enter again : ";
            cin>>time[i];
            system(" color 0F");
        }
        while(time[i]%100 > 60)
        {
            system(" color 4F");
            cout<<endl<<"Time format is wrong. Please enter again : ";
            cin>>time[i];
            system(" color 0F");
        }
        cout<<"Enter the destination of the student "<<i+1<<" : ";
        cin>>dest[i];
        while(dest[i] < 0 || dest[i] > 24 || dest[i]==16 )
        {
            system(" color 4F");
            cout<<endl<<"Services not serving at that location. Please enter again : ";
            cin>>dest[i];
            system(" color 0F");
        }
        cout<<endl;
    }

//    system("cls");
//    show_map();
    sort_time(time, dest, person);
    //cout<<endl<<"After Sorting : "<<endl;
    //for(int i = 0; i < 20; i++)
    //{
        //   cout<<"Person : "<<person[i]<<endl;
        //  cout<<"Time : "<<time[i]<<endl;
        //  cout<<"Dest : "<<dest[i]<<endl;
    //}
        time_grouping(person,time,dest);

        return 0;
    }
