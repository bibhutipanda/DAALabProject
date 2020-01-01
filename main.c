#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct city {
    int id;
    char cityname[20];
    int n;
};

struct nodes {
    int id;
    char cityname[20];
    int n;
    struct nodes *next;
};
struct nodes* load(char cityname[])
{
    FILE *infile;
    struct city input;
    struct nodes *node=NULL;
    infile = fopen (cityname,"rb");
    fread (&input, sizeof(struct city), 1, infile);
    node=(struct nodes *)malloc(sizeof(struct nodes));
    struct nodes *temp=node;
    strcpy(node->cityname,input.cityname);
    node->id=input.id;
    node->n=input.n;
    node->next=NULL;
    while (fread (&input, sizeof(struct city), 1, infile)==1)
    {
        node->next=(struct nodes *)malloc(sizeof(struct nodes));
        node=node->next;
        node->id=input.id;
        strcpy(node->cityname,input.cityname);
        node->n=input.n;
        node->next=NULL;
    }
    fclose(infile);
    return temp;
}

typedef struct
{
    int source;
    int dest; //destination
    int weight;
} node;


void heapify(node arr[] , int e , int p)
{
    int gt=p;
    int lc = 2*p+1;
    int rc = 2*p+2;
    if(lc<e && arr[lc].weight>arr[gt].weight)
        gt=lc;
    if(rc<e && arr[rc].weight>arr[gt].weight)
        gt=rc;
    if(gt!=p)
    {
        node temp = arr[p];
        arr[p]= arr[gt];
        arr[gt] = temp;
        heapify(arr,e,gt);
    }
}
void heap_sort(node arr[] , int e) // USING HEAP SORT TO SORT SET OF WEIGHT
{
    int i;
    for(i=(e+1)/2; i>=0; i--)
    {
        heapify(arr,e,i);
    }
    int cs=e;
    while(cs>1)
    {
        node temp = arr[0];
        arr[0]= arr[cs-1];
        arr[cs-1] = temp;
        cs--;
        heapify(arr,cs,0);
    }
}

int find(int v,int parent[], int n)
{
    if(v==parent[v])
    {
        return v;
    }
    else
    {
        return find(parent[v],parent,n);
    }
}
int krushal(int n, node arr[])
{
    int parent[n];
    for(int i=0; i<n; i++)
    {
        parent[i]=i;
    }

    node *farr = (node*)malloc((n-1)*sizeof(node));
    int i=0;
    int count = 0;
    while(count !=n-1) //AS N-1 IS THE NUMBER OF FINAL EDGE
    {
        node current_edge = arr[i];

        int source_parent = find(current_edge.source,parent,n);
        int dest_parent = find(current_edge.dest,parent,n);
        if(source_parent!=dest_parent)
        {
            farr[count]=current_edge;
            parent[source_parent]=dest_parent;
            count++;
        }
        i++;
    }

    int cost =0;
    for(int i=0; i<n-1; i++)
    {
        cost = cost + farr[i].weight;
    }

    return cost;
}


int krus(int krush[][3], int n,int e)
{
    node *arr = (node*)malloc(e*sizeof(node));
    for(int j=0; j<e; j++)
    {
        arr[j].source = krush[j][0];
        arr[j].dest = krush[j][1];
        arr[j].weight = krush[j][2];
    }

    heap_sort(arr,e);
    return krushal(n,arr);
}

int find_min_vertex(int distance[],int visited[],int n)
{
    int min_vertex =-1;
    for(int i=0; i<n; i++)
    {
        if(visited[i]==0 &&(min_vertex==-1 || distance[i]<distance[min_vertex]))
        {
            min_vertex=i;
        }
    }
    return min_vertex;
}

int dijk(int edges[5][5],int n,int s,int d)
{
    int distance[n];
    int visited[n];

    for(int i=0; i<n; i++)
    {
        distance[i] = 99999;
        visited[i] = 0 ;
    }

    distance[s]=0;

    for(int i=0; i<n-1; i++)
    {
        int min_vertex = find_min_vertex(distance,visited,n);
        visited[min_vertex] = 1;
        for(int j=0; j<n; j++)
        {
            if(edges[min_vertex][j]!=0 && visited[j]==0)
            {
                int dist = distance[min_vertex] + edges[min_vertex][j];
                if(dist<distance[j])
                {
                    distance[j]=dist;
                }
            }
        }
    }
    return distance[d];
}

void createMap(char name[],int n)
{
    /* name: Name of the file
     * n: Number of connected nodes with that node
    */
    struct city input;
    struct city *node;
    FILE *outfile;
    char cityname[]="Maps/";
    strcat(cityname,name);

    outfile = fopen(cityname, "wb");
    if (outfile == NULL)
    {
        exit(1);
    }

    while (n--)
    {
        node = (struct city *) malloc(sizeof(struct city));
        printf("Enter connected city id: ");
        scanf("%d",&(node->id));
        printf("Enter connected city name: ");
        scanf("%s", node->cityname);
        printf("Enter cost from source city: ");
        scanf("%d", &(node->n));
        fwrite(node, sizeof(struct city), 1, outfile);
        printf ("City name = %s\nCost = %d\n",node->cityname,node->n);
    }

    fclose(outfile);
}

void main () {
    struct nodes *city[5],*place[4];
    int src,dest,i,j;
    char sourcecity[20],destcity[20];
    printf("1. Delhi\n2. Mumbai\n3. Jaipur\n4. Kolkata\n5. Goa\n");
    printf("Choose source: ");
    scanf("%d",&src);
    switch(src)
    {
        case 1:
            strcpy(sourcecity,"Delhi.dat");
            break;
        case 2:
            strcpy(sourcecity,"Mumbai.dat");
            break;
        case 3:
            strcpy(sourcecity,"Jaipur.dat");
            break;
        case 4:
            strcpy(sourcecity,"Kolkata.dat");
            break;
        case 5:
            strcpy(sourcecity,"Goa.dat");
            break;
    }
    printf("Choose destination: ");
    scanf("%d",&dest);
    while(src==dest)
    {
        printf("Source and destination cannot be same, choose destination again: ");
        scanf("%d",&dest);
    }

    switch(dest)
    {
        case 1:
            strcpy(destcity,"Delhi.dat");
            break;
        case 2:
            strcpy(destcity,"Mumbai.dat");
            break;
        case 3:
            strcpy(destcity,"Jaipur.dat");
            break;
        case 4:
            strcpy(destcity,"Kolkata.dat");
            break;
        case 5:
            strcpy(destcity,"Goa.dat");
            break;
    }

    printf("Loading maps...\n");
    city[0]=load("Maps/Delhi.dat");
    city[1]=load("Maps/Mumbai.dat");
    city[2]=load("Maps/Jaipur.dat");
    city[3]=load("Maps/Kolkata.dat");
    city[4]=load("Maps/Goa.dat");
    printf("Maps loaded successfully\n");

    int adjacency[5][5];
    int matrix[4][4];

    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            adjacency[i][j]=0;

    for(i=0; i<5; i++)
    {
        while(city[i]!=NULL)
        {
            adjacency[i][city[i]->id]=city[i]->n;
            city[i]=city[i]->next;
        }
    }

    printf("Adjacency matrix representation for all cities:\n");
    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
        {
            printf("%2d\t",adjacency[i][j]);
        }
        printf("\n\n");
    }

    int statecost=dijk(adjacency,5,src-1,dest-1);

    switch(dest-1)
    {
        case 0:
            place[0]=load("Maps/DelhiHotel.dat");
            place[1]=load("Maps/QutubMinar.dat");
            place[2]=load("Maps/RedFort.dat");
            place[3]=load("Maps/IndiaGate.dat");
            break;
        case 1:
            place[0]=load("Maps/MumbaiHotel.dat");
            place[1]=load("Maps/ElephantaCaves.dat");
            place[2]=load("Maps/GatewayOfIndia.dat");
            place[3]=load("Maps/HotelTaj.dat");
            break;
        case 2:
            place[0]=load("Maps/JaipurHotel.dat");
            place[1]=load("Maps/Fort.dat");
            place[2]=load("Maps/Palace.dat");
            place[3]=load("Maps/Museum.dat");
            break;
        case 3:
            place[0]=load("Maps/KolkataHotel.dat");
            place[1]=load("Maps/Dakshineswar.dat");
            place[2]=load("Maps/VictoriaMemorial.dat");
            place[3]=load("Maps/HowrahBridge.dat");
            break;
        case 4:
            place[0]=load("Maps/GoaHotel.dat");
            place[1]=load("Maps/Anjuna.dat");
            place[2]=load("Maps/Panaji.dat");
            place[3]=load("Maps/Dona.dat");
            break;
    }

    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            matrix[i][j]=0;

    int krush[100][3];

    for(i=0; i<4; i++)
    {
        while(place[i]!=NULL)
        {
            matrix[i][place[i]->id]=place[i]->n;
            place[i]=place[i]->next;
        }
    }

    printf("Adjacency matrix representation for %s:\n",destcity);
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            printf("%2d\t",matrix[i][j]);
        }
        printf("\n\n");
    }

    int k=0;
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            if((i<j)&&matrix[i][j]!=0)
            {
                krush[k][0]=i;
                krush[k][1]=j;
                krush[k][2]=matrix[i][j];
                k++;
            }
        }

    int citycost=krus(krush,4,k);

    printf("Cost to move from %s to %s is %d\n",sourcecity,destcity,statecost);
    printf("Cost for travelling in city %s is %d\n",destcity,citycost);
    printf("Total cost for the tour is: %d\n",statecost+citycost);
}