/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"SauceCodePro Nerd Font Mono:size=12",
	"BlexMono Nerd Font:size=12",
	"Fira Code:size=12",
	"Hack:size=12",
	"terminal:size=12",
	"monospace:size=12",
};

static const char fg[]        = "#ebdbb2";
static const char fgsel[]     = "#fbf1c7";
static const char bg[]        = "#282828";
static const char bgsel[]     = "#d79921";

static const char *colors[][3] = {
	/*               fg, bg, border   */
	[SchemeNorm] = { fg, bg, bg },
	[SchemeSel]  = { fgsel, bgsel, bgsel  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "KeePassXC",NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol, arrange function */
	{ "舘", tile    }, /* first entry is default */
	{ "",  NULL    }, /* no layout function means floating behavior */
	{ "",  monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]        = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]  = { "dmenu_run", NULL };
static const char *termcmd[]   = { "st", NULL };
static const char *brightinc[] = { "brightness", "inc", NULL };
static const char *brightdec[] = { "brightness", "dec", NULL };
static const char *volinc[]    = { "volume", "inc", NULL };
static const char *voldec[]    = { "volume", "dec", NULL };
static const char *screenshot[] = { "screenshot", NULL };

// *** /usr/include/X11/keysymdef.h
#include "movestack.c"
static Key keys[] = {
	/* modifier,          key,                      function,       argument */
	{ MODKEY|ControlMask, XK_x,                     spawn,          {.v = screenshot  } },
	{ MODKEY,             XK_f,                     spawn,          {.v = dmenucmd    } },
	{ MODKEY,             XK_Return,                spawn,          {.v = termcmd     } },
	{ 0,                  XF86XK_MonBrightnessUp,   spawn,          {.v = brightinc   } },
	{ 0,                  XF86XK_MonBrightnessDown, spawn,          {.v = brightdec   } },
	{ 0,                  XF86XK_AudioRaiseVolume,  spawn,          {.v = volinc      } },
	{ 0,                  XF86XK_AudioLowerVolume,  spawn,          {.v = voldec      } },
	{ MODKEY,             XK_KP_Subtract,           setgaps,        {.i = -5          } },
	{ MODKEY,             XK_KP_Add,                setgaps,        {.i = +5          } },
	{ MODKEY,             XK_KP_Multiply,           setgaps,        {.i = GAP_RESET   } },
	{ MODKEY|ShiftMask,   XK_KP_Multiply,           setgaps,        {.i = GAP_TOGGLE  } },
	{ MODKEY,             XK_h,                     movestack,      {.i = -1          } },
	{ MODKEY,             XK_l,                     movestack,      {.i = +1          } },
	{ MODKEY,             XK_j,                     focusstack,     {.i = +1          } },
	{ MODKEY,             XK_k,                     focusstack,     {.i = -1          } },
	{ MODKEY|ShiftMask,   XK_h,                     setmfact,       {.f = -0.05       } },
	{ MODKEY|ShiftMask,   XK_l,                     setmfact,       {.f = +0.05       } },
	{ MODKEY,             XK_o,                     incnmaster,     {.i = +1          } },
	{ MODKEY,             XK_i,                     incnmaster,     {.i = -1          } },
	{ MODKEY,             XK_t,                     setlayout,      {.v = &layouts[0] } },
	{ MODKEY,             XK_n,                     setlayout,      {.v = &layouts[1] } },
	{ MODKEY,             XK_m,                     togglefullscr,  {0                } },
	{ MODKEY,             XK_space,                 setlayout,      {0                } },
	{ MODKEY|ShiftMask,   XK_space,                 togglefloating, {0                } },
	{ MODKEY,             XK_Tab,                   view,           {0                } },
	{ MODKEY,             XK_0,                     view,           {.ui = ~0         } },
	{ MODKEY|ShiftMask,   XK_0,                     tag,            {.ui = ~0         } },
	{ MODKEY,             XK_b,                     togglebar,      {0                } },
	{ MODKEY,             XK_period,                focusmon,       {.i = +1          } },
	{ MODKEY|ShiftMask,   XK_period,                tagmon,         {.i = +1          } },
	/// only have 2 monitors, so it doesn't matter which direction i go in.
	/* { MODKEY,             XK_asterisk,                 focusmon,       {.i = -1          } }, */
	/* { MODKEY|ShiftMask,   XK_asterisk,                 tagmon,         {.i = -1          } }, */
	{ MODKEY,             XK_q,                     killclient,     {0                } },
	{ MODKEY|ControlMask, XK_q,                     quit,           {0                } },
	TAGKEYS(XK_a,         0) // idk (console)
	TAGKEYS(XK_d,         1) // development (programming)
	TAGKEYS(XK_w,         2) // web (browser)
	TAGKEYS(XK_s,         3) // search (file manager)
	TAGKEYS(XK_v,         4) // video (multimedia)
	TAGKEYS(XK_e,         5) // idk (music)
	TAGKEYS(XK_c,         6) // chat
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

