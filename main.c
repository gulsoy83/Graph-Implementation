#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
	char komsuisim[200];
    struct list *dugum;
	struct node *next;
};
typedef struct node odugumunkomsulari;

struct list{
	char benhanginodum[200];
	odugumunkomsulari *head;
	unsigned int kackomsumvar;
	unsigned int takipcimkac;
	
	unsigned int mark;
	unsigned int distance;
	struct list *distancetowho;
	struct list *parent;
	
	struct list *ileri;
};
typedef struct list dugumler;

struct graph{
	unsigned int dugumsayisi;
	dugumler *head;
};

typedef struct graph graf;



graf* creategraf(){
	graf *gp = (graf *) malloc(sizeof(graf));
	if(gp==NULL) exit(1);
	gp->dugumsayisi=0;
	gp->head=NULL;
	
	return gp;
}

dugumler* yaprakekle(graf *gp, char *ekleneceknode){
	gp->dugumsayisi++;
	
	if(gp->head==NULL){
		gp->head = (dugumler *) malloc (sizeof(dugumler));
	    if (gp->head==NULL){
	    	printf("bellek hatasi.\n");
	    	exit(-1);
		}
	
	    strcpy(gp->head->benhanginodum,ekleneceknode);
	    gp->head->head=NULL;
	    gp->head->ileri=NULL;
	    gp->head->kackomsumvar=0;
	    gp->head->distance=0;
	    gp->head->mark=0;
	    gp->head->takipcimkac=0;
	    gp->head->parent=NULL;
	    return gp->head;
	}
else{
		
	dugumler *tmp = gp->head;
	while((tmp!=NULL)) {
		if(strcmp(tmp->benhanginodum,ekleneceknode)==0){
			gp->dugumsayisi--;
			return tmp;
		}
		else
		tmp=tmp->ileri;
	}
	
		dugumler *newd = (dugumler *) malloc (sizeof(dugumler));
		if(newd==NULL){
			printf("bellek hatasi\n");
			exit(-1);
		}
		strcpy(newd->benhanginodum,ekleneceknode);
		newd->ileri=NULL;
		newd->head=NULL;
		newd->kackomsumvar=0;
		newd->distance=0;
		newd->takipcimkac=0;
		newd->mark=0;
		newd->parent=NULL;
	   
	    
		tmp = gp->head;
		
		while(tmp->ileri!=NULL)
		tmp=tmp->ileri;
		
		tmp->ileri=newd;
	
       return newd;
	
}
}

void komsuekle(graf *gp, dugumler *kimekomsu, dugumler *eklenecekkomsu){
	dugumler *tmp;
	
	if (kimekomsu->head == NULL){
		kimekomsu->head = (odugumunkomsulari *) malloc (sizeof(odugumunkomsulari));
		if(kimekomsu->head ==NULL) exit(1);
		kimekomsu->head->next=NULL;
		strcpy(kimekomsu->head->komsuisim,eklenecekkomsu->benhanginodum);
		kimekomsu->head->dugum= eklenecekkomsu;
        kimekomsu->kackomsumvar=1;
	}
	else{
		odugumunkomsulari *t1 = kimekomsu->head;
		while(t1!=NULL){
			if(strcmp(t1->komsuisim,eklenecekkomsu->benhanginodum)==0){
			return;	
			}
			t1=t1->next;
		}
		
		odugumunkomsulari *old = kimekomsu->head;
		while(old->next!=NULL) old = old->next;
		t1 = (odugumunkomsulari *) malloc (sizeof(odugumunkomsulari));
		if(t1==NULL) exit(1);
		t1->next=NULL;
		strcpy(t1->komsuisim,eklenecekkomsu->benhanginodum);
		t1->dugum=eklenecekkomsu;
		old->next=t1;
		kimekomsu->kackomsumvar++;
	}
	
}

void yapraklariyazdir(graf *gp){
	if(gp==NULL){
		printf("Graf tanimlanmamis.\n");
		return;
	}
	if(gp->head==NULL){
		printf("Hicbir dugum yok.\n");
		return;
	}
	int i=0;
	printf("Dugumler yazdiriliyor.\n");
	dugumler *tmp = gp->head;
	while(tmp!=NULL){
		i++;
		printf("%d: %s\n",i,tmp->benhanginodum);
		tmp=tmp->ileri;
	}
}

void komsulariyazdir(graf *mg){
    dugumler *benimkomsularimneler;
    benimkomsularimneler = mg->head;
    
    printf("\nKomsular yazdiriliyor.\n\n");
    
    while(benimkomsularimneler!=NULL){
    	
        odugumunkomsulari *tmp= benimkomsularimneler->head;
	    if(tmp == NULL){
		    printf("\\/\\/ %s dugumunun komsusu yok ! (%d tane)\n",benimkomsularimneler->benhanginodum, benimkomsularimneler->kackomsumvar);
		
		
    	}
	    else{

	        printf("\\/\\/ %s dugumunun komsulari: %d tane;\n* ",benimkomsularimneler->benhanginodum, benimkomsularimneler->kackomsumvar);
	        
			while(tmp->next!=NULL){
		        printf("%s, ",tmp->komsuisim);
		        tmp = tmp->next;
        	}
        	 printf("%s.\n\n",tmp->komsuisim);
		    
        }	
    	benimkomsularimneler=benimkomsularimneler->ileri;
	}
 
}


void encokbg (graf *mg){
	dugumler *tmp=mg->head;
	int i,n=0;
	unsigned int toplam=0;
    n=mg->dugumsayisi;
	
	
	printf("EN COK BAGLANTISI OLAN KULLANICILAR:\n");
	
	tmp=mg->head;
	
	int komsumkac[n];
	char benkimim [n][200];
	for(i=0;i<n;i++){
		komsumkac[i] = tmp->kackomsumvar;
		toplam+=tmp->kackomsumvar;
		strcpy(benkimim[i],tmp->benhanginodum);
		tmp=tmp->ileri;
	}
	int j,min,temp;
	
	for(i=0;i<n-1;i++){
	    min=i;
		
		for(j=i+1;j<n;j++){
			
			if(komsumkac[j] < komsumkac[min])
			min=j;
		}
		
		temp=komsumkac[i];
		komsumkac[i]=komsumkac[min];
		komsumkac[min]=temp;
		
		char tkel[200];
		strcpy(tkel,benkimim[i]);
		strcpy(benkimim[i],benkimim[min]);
		strcpy(benkimim[min],tkel);
	  
	}
	int sayac=0;
	printf("\nEn cok takip edenler;\n");
	for(i=n-1;i>-1;i--){
        
	    printf("> %s: adli kisi su kadar kisiyi takip ediyor: %d\n",benkimim[i],komsumkac[i]);
	    sayac++;
	    if(sayac>=10) break;
	}
	printf("Ortalama: %d, medyan: %d\n",toplam/n,komsumkac[n/2]);
	
	
	printf("\n");
	
    toplam=0;	
	tmp=mg->head;
		while(tmp!=NULL){
	    i=0;
		dugumler *tmp2 = mg->head;
	    while(tmp2!=NULL){
	    	
	      odugumunkomsulari *den = tmp2->head;
		  while(den!=NULL){
			if(strcmp(tmp->benhanginodum,den->komsuisim)==0)
			i++;
			
			den=den->next;
        	}
	    	
	    	tmp2=tmp2->ileri;
		}
		
	    tmp->takipcimkac=i;
		toplam+=tmp->takipcimkac;
		tmp=tmp->ileri;
	}
	
	
	int takipcimkac[n];
    tmp=mg->head;
	for(i=0;i<n;i++){
		takipcimkac[i] = tmp->takipcimkac;
		strcpy(benkimim[i],tmp->benhanginodum);
		tmp=tmp->ileri;
	}
	
	
	for(i=0;i<n-1;i++){
	    min=i;
		
		for(j=i+1;j<n;j++){
			
			if(takipcimkac[j] < takipcimkac[min])
			min=j;
		}
		
		temp=takipcimkac[i];
		takipcimkac[i]=takipcimkac[min];
		takipcimkac[min]=temp;
		
		char tkel[200];
		strcpy(tkel,benkimim[i]);
		strcpy(benkimim[i],benkimim[min]);
		strcpy(benkimim[min],tkel);
	  
	}
	
	//
	sayac=0;
	printf("En cok takipcisi olanlar;\n");	
	for(i=n-1;i>-1;i--){
        
	    printf("> %s: adli kisi su kadar takipciye sahip: %d\n",benkimim[i],takipcimkac[i]);
	    sayac++;
	    if(sayac>=10) break;
	}
	printf("Ortalama: %d, medyan: %d\n",toplam/n,takipcimkac[n/2]);
	printf("\n\n");
    
    
    
    printf("Toplam baglanti sayisi bilgileri;\n");
	toplam=0;
	tmp=mg->head;
	int topbagkac[n];
	for(i=0;i<n;i++){
		topbagkac[i] = tmp->kackomsumvar+tmp->takipcimkac;
		toplam+=topbagkac[i];
		strcpy(benkimim[i],tmp->benhanginodum);
		tmp=tmp->ileri;
	}
	
	
	for(i=0;i<n-1;i++){
	    min=i;
		
		for(j=i+1;j<n;j++){
			
			if(topbagkac[j] < topbagkac[min])
			min=j;
		}
		
		temp=topbagkac[i];
		topbagkac[i]=topbagkac[min];
		topbagkac[min]=temp;
		
		char tkel[200];
		strcpy(tkel,benkimim[i]);
		strcpy(benkimim[i],benkimim[min]);
		strcpy(benkimim[min],tkel);
	  
	}
	
	sayac=0;
	printf("En cok baglantisi olanlar;\n");	
	for(i=n-1;i>-1;i--){
        
	    printf("> %s: adli kisi su kadar baglantiya sahip: %d\n",benkimim[i],topbagkac[i]);
	    sayac++;
	    if(sayac>=10) break;
	}
	printf("Ortalama: %d, medyan: %d\n",toplam/n,topbagkac[n/2]);

    return;
}

struct kuyrukuyesi{
    dugumler *key;
    int priority;
    struct kuyrukuyesi *next;
};

struct kuyruk{
	struct kuyrukuyesi *front,*rear;
};
 
struct kuyrukuyesi* newNode(dugumler *d, int p) { 
    struct kuyrukuyesi* temp = (struct kuyrukuyesi*)malloc(sizeof(struct kuyrukuyesi)); 
    if(temp==NULL) exit(1);
	temp->key=d;
    temp->next = NULL; 
    temp->priority=p;
    return temp; 
} 
  
struct kuyruk* createqueue() { 
    struct kuyruk* q = (struct kuyruk*)malloc(sizeof(struct kuyruk)); 
    if(q==NULL) exit(1);
    q->front = q->rear = NULL; 
    return q; 
} 
  
dugumler* dequeue(struct kuyruk* q){  
    if (q->front == NULL) 
        return; 
  
    struct kuyrukuyesi* temp = q->front; 
    q->front = q->front->next; 
  
    if (q->front == NULL) 
        q->rear = NULL; 
        
    dugumler* yedek;
	yedek = temp->key;    
    free(temp); 
    return yedek;
} 
void enqueue(struct kuyruk* q, dugumler *k,int p) { 
    struct kuyrukuyesi* temp = newNode(k,p); 
    struct kuyrukuyesi *start =q->front;
	if (q->rear == NULL) { 
        q->front = q->rear = temp; 
        return; 
    } 
    if(q->front->priority>p){
    	temp->next=q->front;
    	q->front=temp;
	}
	else{
		while(start->next!=NULL && start->next->priority<p){
			
			start=start->next;
		}
		temp->next = start->next;
		start->next = temp;
	}
   
} 

int isempty(struct kuyruk *q){
	if(q->front==NULL)
	return 0;
	return 1;
}


void dijkstra (graf *mg, dugumler *src){
	struct kuyruk *q =createqueue();
	
	
	src->distance=0;
	dugumler *tmp =mg->head;
	while(tmp!=NULL){
		if(tmp!=src){
			tmp->distance=INT_MAX;
			tmp->parent=NULL;
			tmp->distancetowho=src;
		}
		
		enqueue(q,tmp,tmp->distance);
		
		tmp=tmp->ileri;
	}
	
	
	while(isempty(q)){
		tmp = dequeue(q);
		
		
		
		odugumunkomsulari *k = tmp->head;
		while(k!=NULL){
			
			
			if( k->dugum->distance > (tmp->distance+1)){
			k->dugum->distance= tmp->distance+1;
			k->dugum->parent=tmp;
	    	}
			k=k->next;
		
		}
		
	}
	
	return;
}
void tumdugumciftlerienkisayol(graf *myg){
	dugumler *tmp2=myg->head;
	FILE *dsonuc =fopen("distances.txt","w");
    if (dsonuc==NULL){
		printf("Dosya olusturulamadi.\n");
		exit(1);
	}
	char line[200];
	
	printf("\nTum dugum ciftleri arasindaki en kisa yollar icin 'distances.txt' yi inceleyin.\n");
    fprintf(dsonuc,"Tum dugum ciftleri arasindaki en kisa yollar.\nNOT: dugumler arasi mesafe sonsuzsa, yani yol yoksa asagiya yazdirilmamistir.\n");
	
	while(tmp2!=NULL){
    //her dugum icin dijkstra'yi cagirip, o dugum start olacak sekilde shortes distance		
    //hesabi yapiyorum. bu distance bilgisi dugumun struct'unda tutuluyor. kolay olsun diye ayri dizilerle ugrasmadim.
	  dijkstra(myg,tmp2);
	 //bu islemden sonra, icte bir dongu daha yapip butun dugumleri tarayip distance bilgisini dosyaya atiyorum. 
	  dugumler *tmp= myg->head;
	  strcpy(line,"\nShortest paths to ... for start point: ");
	  strcat(line,tmp2->benhanginodum);
	  strcat(line,"\n");
	  fprintf(dsonuc,"%s",line);
	  //printf("\nShortest paths to ... for start point: %s\n",tmp2->benhanginodum);
      
	  //dosyaya yazdirirken, bir dugumden digerine mesafe sonsuzsa, bunu infinite olarak yazdirabilirim ya da yazdirmamayi secebilirim.
	  while(tmp!=NULL){
		if(tmp->distance!=INT_MAX){
		  strcpy(line,tmp->benhanginodum);
		  strcat(line,": ");
		  char gecici[200];
		  sprintf(gecici,"%d\n",tmp->distance);
		  strcat(line,gecici);
		  fprintf(dsonuc,"%s",line);
		  //printf("%s: %d\n",tmp->benhanginodum,tmp->distance);
		}
		else{
		  /*strcpy(line,tmp->benhanginodum);
		  strcat(line,": ");
		  strcat(line,"infinite\n");
		  fprintf(dsonuc,"%s",line);
			*/
		}
		tmp=tmp->ileri;
	  }
	
	tmp2=tmp2->ileri;
	
	}
	fclose(dsonuc);
}

////////////////


void aradabulunma(graf *mg){
    /*
	
	//floyd warshall algoritmasini implemente etmeye calistim ama yapamadim.
	
	int n=mg->dugumsayisi;
    dugumler *in, *jn;
    int dist[n][n],i,j,k;
    
	    
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			int sayac=i;
			in=mg->head;
			while(sayac>0){
				in=in->ileri;
				sayac--;
			}
			sayac=j;
			jn=mg->head;
			while(sayac>0){
				jn=jn->ileri;
				sayac--;
			}
			dijkstra(mg,in);
			dist[i][j]=jn->distance;
		}
	}





	yapraklariyazdir(mg);printf("\n");
for(i=0;i<n;i++){

		for(j=0;j<n;j++){
		if(dist[i][j]!=INT_MAX)
          printf("%d ",dist[i][j]);
          else printf("? ");
    }
		printf("\n");
		}
		
for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
      	
        if ( dist[i][k] != INT_MAX &&  dist[k][j] != INT_MAX &&  dist[i][k] + dist[k][j] < dist[i][j])
        
 dist[i][j] = dist[i][k] + dist[k][j];
          
      }
    }
  }
	
	printf("\n");
for(i=0;i<n;i++){

		for(j=0;j<n;j++){
		if(dist[i][j]!=INT_MAX)
          printf("%d ",dist[i][j]);
          else printf("? ");
    }
		printf("\n");
		}

*/
	return;
}

void dosyayiisle(char fname[]){
	char tmp1[200],tmp2[200];	
	char line[200];
	
	FILE *fp = fopen(fname,"r");
	if (fp==NULL){
		printf("Dosya acilamadi.\nSNAgraph.csv dosyasinin duzgun olusturuldugundan ve program ile ayni lokasyonda bulundugundan emin olun.\n");
		exit(1);
	}
    
    graf *mygraf;
	mygraf=creategraf();
    
    fseek(fp,0,SEEK_SET);
	fgets(line,sizeof(line),fp);
    //ilk satiri atladim.
	
	while( fgets(line,sizeof(line),fp)){
     
	 	//dosyadan satiri aliyorum virgulden oncesini ve sonrasini ayiriyorum.
		int k=0;
    	while(line[k]!=','){
    	  tmp1[k]=line[k];
		  k++;	
		}
		tmp1[k]='\0';
		k++;
		int l=0;
		while(line[k]!='\n'){
    	  tmp2[l]=line[k];
		  k++;
		  l++;	
		}
		tmp2[l]='\0';
		
		

		
		
		dugumler *den,*den2;
		den=yaprakekle(mygraf,tmp1);
        den2=yaprakekle(mygraf,tmp2);
        //bunlari yaprak olarak ekliyorum ve sonra da aralarini bagliyorum.
        komsuekle(mygraf,den,den2);
       
     
     	
	}
    //yapraklariyazdir(mygraf);
	//komsulariyazdir(mygraf);
	
	
	
	
	encokbg(mygraf);
	//en cok baglanti sayilari icin yazdigim fonk
	
	tumdugumciftlerienkisayol(mygraf);
	//dugumler arasi mesafeyi bir dosyaya yazdiran fonk.
	
	aradabulunma(mygraf);
	//all pairs shortest path floyd algoritmasi kullanarak
	//centrality'yi yapmaya calistim ama olmadi, bu kisim calismiyor
	//o yuzden fonksiyon icindeki kodu yorum gibi gizledim.
	
	
	
	
	
	//printf("%d",mygraf->dugumsayisi);    		
  	fclose(fp);
	return;
}
	
	





int main() {

   dosyayiisle("SNAgraph.csv");
    
	return 0;
}
