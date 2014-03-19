#define MASUmax 8
#define TAISENSUU 100

static void J_tekinote();
static void J_turn(int);
static void J_hyouzi();
static void J_zyunbi();
static void J_passJud(int);
static void J_hikkurikaeshi();
static void J_KANAME(int);
static void J_shiaimae();
static void J_endflag(int);
static void J_kekkahyouzi();
static int J_BAN[MASUmax+2][MASUmax+2];
static int J_flag[10];
static int J_HINT[MASUmax*MASUmax+1];
static int J_teban;
static int J_TE;
static int J_x,J_y;
static int J_wincount[3]={0,0,0};


