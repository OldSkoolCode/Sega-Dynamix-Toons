

		tsection	.graf


incfpafile	MACRO
		XDEF	_\1
_\1:
		.bin	\1.fpa
		ENDM

incfpcfile	MACRO
		XDEF	_\1
_\1:
		.bin	\1.fpc
		ENDM

incfamfile	MACRO
		XDEF	_\1
_\1:
		.bin	\1.fam
		ENDM



		incfpafile	catakeup
		incfpafile	catangel 
		incfpafile	catate   
		incfpafile	catbanan 	       
		incfpafile	catbomb  
		incfpafile	catbutt  
		incfpafile	catclimb 
		incfpafile	catcrack 
		incfpafile	catcut   
		incfpafile	categg   
		incfpafile	catfish  
		incfpafile	catflail 
		incfpafile	catgum   
		incfpafile	cathairb 
		incfpafile	cathdryr 
		incfpafile	catlunch 
		incfpafile	catpeel  
		incfpafile	catpencl 
		incfpafile	catpiano 
		incfpafile	catpin1  
		incfpafile	catpin2  
		incfpafile	catpin3  
		incfpafile	catpounc 
		incfpafile	catroot  
		incfpafile	catrug   
		incfpafile	catrun   
		incfpafile	catrunaw 
		incfpafile	catsaw   
		incfpafile	catshake 
		incfpafile	catshot  
		incfpafile	catsleep 
		incfpafile	catslide 
		incfpafile	catsmash 
		incfpafile	catsrtch 
		incfpafile	catstop  
		incfpafile	cattake  
		incfpafile	catunnel 
		incfpafile	catvac   
		incfpafile	catwalk  
		incfpafile	catyarn 	

		incfamfile	riptest
		incfamfile	progpart
		incfamfile	speed
		incfamfile	partbin
		incfamfile	clapper
		incfamfile	handall


		incfpafile	sidanvil
		incfpafile	sidbanan
		incfpafile	sidberny
		incfpafile	sidbomb
		incfpafile	sidbonk
		incfpafile	sidbronx
		incfpafile	sidbutt
		incfpafile	sidcheez
		incfpafile	sidclimb
		incfpafile	sidcut
		incfpafile	siddustb
		incfpafile	sidegg
		incfpafile	sidfall
		incfpafile	sidfly
		incfpafile	sidgiggl
		incfpafile	sidgill
		incfpafile	sidgum
		incfpafile	sidgun
		incfpafile	sidhair
		incfpafile	sidhdryr
		incfpafile	sidhless
		incfpafile	sidknif1
		incfpafile	sidknif2
		incfpafile	sidknife
		incfpafile	sidlunch
		incfpafile	sidmiror
		incfpafile	sidninja
		incfpafile	sidpeel
		incfpafile	sidpencl
		incfpafile	sidpiano
		incfpafile	sidpin
		incfpafile	sidragon
		incfpafile	sidrock
		incfpafile	sidroot
		incfpafile	sidrun
		incfpafile	sidsaw
		incfpafile	sidshake
		incfpafile	sidslide
		incfpafile	sidsqeek
		incfpafile	sidstop
		incfpafile	sidtake
		incfpafile	sidtunel
		incfpafile	sidvac
		incfpafile	sidwait
		incfpafile	sidwalk
		incfpafile	sidwhop
		incfpafile	sidwulf


		XDEF	_sidTable

_sidTable:
		dc.l	_sidroot
		dc.l	_sidtake
		dc.l	_sidrun
		dc.l	_sidgiggl
		dc.l	_sidbronx
		dc.l	_sidfall
		dc.l	0
		dc.l	_sidwalk
		dc.l	_sidhair
		dc.l	_sidcut
		dc.l	_sidwhop
		dc.l	_sidclimb
		dc.l	0
		dc.l	_sidgun
		dc.l	_siddustb
		dc.l	_sidbutt
		dc.l	_sidbonk
		dc.l	_sidanvil
		dc.l	_sidcheez
		dc.l	_sidlunch
		dc.l	_sidpiano
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	_sidfly
		dc.l	_sidbomb
		dc.l	_sidshake
		dc.l	_sidragon
		dc.l	_sidhdryr
		dc.l	_sidgum
		dc.l	_sidwait
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	_sidstop
		dc.l	_sidpin
		dc.l	0
		dc.l	_sidslide
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	_sidvac
		dc.l	0
		dc.l	0
		dc.l	_sidtunel
		dc.l	_sidpencl
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	_sidpeel
		dc.l	_sidhless
		dc.l	_sidbanan
		dc.l	0
		dc.l	0
		dc.l	_sidegg
  

		XDEF	_catTable
_catTable:
   		dc.l	_catroot
		dc.l	_catsleep
		dc.l	_catbomb
		dc.l	_catwalk
		dc.l	_catcrack
		dc.l	_catshake
		dc.l	_catrun
		dc.l	_cathairb
		dc.l	0
		dc.l	_catflail
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	_catpounc
		dc.l	_catyarn
		dc.l	_catshot
		dc.l	_catangel
		dc.l	0
		dc.l	0
		dc.l	_catate
		dc.l	_catrunaw
		dc.l	0
		dc.l	_cattake
		dc.l	_catclimb
		dc.l	_catcut
		dc.l	_catstop
		dc.l	_catsmash
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	_catslide
		dc.l	0
		dc.l	0
		dc.l	0
		dc.l	_catpin1
		dc.l	_catpin2
		dc.l	_catpin3
		dc.l	_catvac
		dc.l	0
		dc.l	0
		dc.l	_catpiano
		dc.l	_catgum
		dc.l	_catbutt
		dc.l	_catlunch
		dc.l	_catunnel
		dc.l	_catpencl
		dc.l	0
		dc.l	_catsrtch
		dc.l	0
		dc.l	_catfish
		dc.l	_cathdryr
		dc.l	0
;_catmiror
		dc.l	0
		dc.l	_catpeel
		dc.l	_catbanan
		dc.l	_catrug
		dc.l	0
		dc.l	0
		dc.l	_categg
