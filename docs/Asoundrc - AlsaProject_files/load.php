function isCompatible(){if(navigator.appVersion.indexOf('MSIE')!==-1&&parseFloat(navigator.appVersion.split('MSIE')[1])<6){return false;}return true;}var startUp=function(){mw.config=new mw.Map(true);mw.loader.addSource({"local":{"loadScript":"/main/load.php","apiScript":"/main/api.php"}});mw.loader.register([["site","1383140391",[],"site"],["noscript","1383140391",[],"noscript"],["startup","1406259893",[],"startup"],["filepage","1383140391"],["user.groups","1383140391",[],"user"],["user","1383140391",[],"user"],["user.cssprefs","1406259893",["mediawiki.user"],"private"],["user.options","1406259893",[],"private"],["user.tokens","1383140391",[],"private"],["mediawiki.language.data","1406253218",["mediawiki.language.init"]],["skins.chick","1383140391"],["skins.cologneblue","1383140391"],["skins.modern","1383140391"],["skins.monobook","1383140391"],["skins.nostalgia","1383140391"],["skins.simple","1383140391"],["skins.standard","1383140391"],["skins.vector","1383140391"],["jquery",
"1383140391"],["jquery.appear","1383140391"],["jquery.arrowSteps","1383140391"],["jquery.async","1383140391"],["jquery.autoEllipsis","1383140391",["jquery.highlightText"]],["jquery.byteLength","1383140391"],["jquery.byteLimit","1383140391",["jquery.byteLength"]],["jquery.checkboxShiftClick","1383140391"],["jquery.client","1383140391"],["jquery.collapsibleTabs","1383140391"],["jquery.color","1383140391",["jquery.colorUtil"]],["jquery.colorUtil","1383140391"],["jquery.cookie","1383140391"],["jquery.delayedBind","1383140391"],["jquery.expandableField","1383140391",["jquery.delayedBind"]],["jquery.farbtastic","1383140391",["jquery.colorUtil"]],["jquery.footHovzer","1383140391"],["jquery.form","1383140391"],["jquery.getAttrs","1383140391"],["jquery.highlightText","1383140391"],["jquery.hoverIntent","1383140391"],["jquery.json","1383140391"],["jquery.localize","1383140391"],["jquery.makeCollapsible","1396457383"],["jquery.messageBox","1383140391"],["jquery.mockjax","1383140391"],[
"jquery.mw-jump","1383140391"],["jquery.mwExtension","1383140391"],["jquery.placeholder","1383140391"],["jquery.qunit","1383140391"],["jquery.qunit.completenessTest","1383140391",["jquery.qunit"]],["jquery.spinner","1383140391"],["jquery.suggestions","1383140391",["jquery.autoEllipsis"]],["jquery.tabIndex","1383140391"],["jquery.tablesorter","1383140391"],["jquery.textSelection","1383140391",["jquery.client"]],["jquery.validate","1383140391"],["jquery.xmldom","1383140391"],["jquery.tipsy","1383140391"],["jquery.ui.core","1383140391",["jquery"],"jquery.ui"],["jquery.ui.widget","1383140391",[],"jquery.ui"],["jquery.ui.mouse","1383140391",["jquery.ui.widget"],"jquery.ui"],["jquery.ui.position","1383140391",[],"jquery.ui"],["jquery.ui.draggable","1383140391",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"],"jquery.ui"],["jquery.ui.droppable","1383140391",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget","jquery.ui.draggable"],"jquery.ui"],["jquery.ui.resizable","1383140391",[
"jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.selectable","1383140391",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.sortable","1383140391",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.accordion","1383140391",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.autocomplete","1383140391",["jquery.ui.core","jquery.ui.widget","jquery.ui.position"],"jquery.ui"],["jquery.ui.button","1383140391",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.datepicker","1383140391",["jquery.ui.core"],"jquery.ui"],["jquery.ui.dialog","1383140391",["jquery.ui.core","jquery.ui.widget","jquery.ui.button","jquery.ui.draggable","jquery.ui.mouse","jquery.ui.position","jquery.ui.resizable"],"jquery.ui"],["jquery.ui.progressbar","1383140391",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.slider","1383140391",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],
"jquery.ui"],["jquery.ui.tabs","1383140391",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.effects.core","1383140391",["jquery"],"jquery.ui"],["jquery.effects.blind","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.bounce","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.clip","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.drop","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.explode","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.fade","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.fold","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.highlight","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.pulsate","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.scale","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.shake","1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.slide",
"1383140391",["jquery.effects.core"],"jquery.ui"],["jquery.effects.transfer","1383140391",["jquery.effects.core"],"jquery.ui"],["mediawiki","1383140391"],["mediawiki.api","1383140391",["mediawiki.util"]],["mediawiki.api.category","1383140391",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.edit","1383140391",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.parse","1383140391",["mediawiki.api"]],["mediawiki.api.titleblacklist","1383140391",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.watch","1383140391",["mediawiki.api","user.tokens"]],["mediawiki.debug","1383140391",["jquery.footHovzer"]],["mediawiki.debug.init","1383140391",["mediawiki.debug"]],["mediawiki.feedback","1383140391",["mediawiki.api.edit","mediawiki.Title","mediawiki.jqueryMsg","jquery.ui.dialog"]],["mediawiki.htmlform","1383140391"],["mediawiki.Title","1383140391",["mediawiki.util"]],["mediawiki.Uri","1383140391"],["mediawiki.user","1383140391",["jquery.cookie"]],["mediawiki.util","1396457382",[
"jquery.client","jquery.cookie","jquery.messageBox","jquery.mwExtension"]],["mediawiki.action.edit","1383140391",["jquery.textSelection","jquery.byteLimit"]],["mediawiki.action.history","1383140391",[],"mediawiki.action.history"],["mediawiki.action.history.diff","1383140391",[],"mediawiki.action.history"],["mediawiki.action.view.dblClickEdit","1383140391",["mediawiki.util"]],["mediawiki.action.view.metadata","1396462568"],["mediawiki.action.view.rightClickEdit","1383140391"],["mediawiki.action.watch.ajax","1383140391",["mediawiki.page.watch.ajax"]],["mediawiki.language","1383140391",["mediawiki.language.data"]],["mediawiki.language.init","1383140391"],["mediawiki.jqueryMsg","1383140391",["mediawiki.util","mediawiki.language"]],["mediawiki.libs.jpegmeta","1383140391"],["mediawiki.page.ready","1383140391",["jquery.checkboxShiftClick","jquery.makeCollapsible","jquery.placeholder","jquery.mw-jump","mediawiki.util"]],["mediawiki.page.startup","1383140391",["jquery.client","mediawiki.util"]]
,["mediawiki.page.watch.ajax","1396487538",["mediawiki.page.startup","mediawiki.api.watch","mediawiki.util"]],["mediawiki.special","1383140391"],["mediawiki.special.block","1383140391",["mediawiki.util"]],["mediawiki.special.changeemail","1397777475",["mediawiki.util"]],["mediawiki.special.changeslist","1383140391",["jquery.makeCollapsible"]],["mediawiki.special.movePage","1383140391",["jquery.byteLimit"]],["mediawiki.special.preferences","1383140391"],["mediawiki.special.recentchanges","1383140391",["mediawiki.special"]],["mediawiki.special.search","1396457395"],["mediawiki.special.undelete","1383140391"],["mediawiki.special.upload","1398253708",["mediawiki.libs.jpegmeta","mediawiki.util"]],["mediawiki.special.javaScriptTest","1383140391",["jquery.qunit"]],["mediawiki.tests.qunit.testrunner","1383140391",["jquery.qunit","jquery.qunit.completenessTest","mediawiki.page.startup","mediawiki.page.ready"]],["mediawiki.legacy.ajax","1383140391",["mediawiki.util","mediawiki.legacy.wikibits"]]
,["mediawiki.legacy.commonPrint","1383140391"],["mediawiki.legacy.config","1383140391",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.IEFixes","1383140391",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.mwsuggest","1383140391",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.preview","1383140391",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.protect","1383140391",["mediawiki.legacy.wikibits","jquery.byteLimit"]],["mediawiki.legacy.shared","1383140391"],["mediawiki.legacy.oldshared","1383140391"],["mediawiki.legacy.upload","1383140391",["mediawiki.legacy.wikibits","mediawiki.util"]],["mediawiki.legacy.wikibits","1383140391",["mediawiki.util"]],["mediawiki.legacy.wikiprintable","1383140391"]]);mw.config.set({"wgLoadScript":"/main/load.php","debug":false,"skin":"vector","stylepath":"/main/skins","wgUrlProtocols":
"http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/|irc\\:\\/\\/|ircs\\:\\/\\/|gopher\\:\\/\\/|telnet\\:\\/\\/|nntp\\:\\/\\/|worldwind\\:\\/\\/|mailto\\:|news\\:|svn\\:\\/\\/|git\\:\\/\\/|mms\\:\\/\\/|\\/\\/","wgArticlePath":"/main/index.php/$1","wgScriptPath":"/main","wgScriptExtension":".php","wgScript":"/main/index.php","wgVariantArticlePath":false,"wgActionPaths":{},"wgServer":"http://www.alsa-project.org","wgUserLanguage":"en","wgContentLanguage":"en","wgVersion":"1.20alpha","wgEnableAPI":true,"wgEnableWriteAPI":true,"wgDefaultDateFormat":"dmy","wgMonthNames":["","January","February","March","April","May","June","July","August","September","October","November","December"],"wgMonthNamesShort":["","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"],"wgMainPageTitle":"Main Page","wgFormattedNamespaces":{"-2":"Media","-1":"Special","0":"","1":"Talk","2":"User","3":"User talk","4":"AlsaProject","5":"AlsaProject talk","6":"File","7":"File talk","8":"MediaWiki","9":
"MediaWiki talk","10":"Template","11":"Template talk","12":"Help","13":"Help talk","14":"Category","15":"Category talk","100":"Matrix","101":"Matrix Talk"},"wgNamespaceIds":{"media":-2,"special":-1,"":0,"talk":1,"user":2,"user_talk":3,"alsaproject":4,"alsaproject_talk":5,"file":6,"file_talk":7,"mediawiki":8,"mediawiki_talk":9,"template":10,"template_talk":11,"help":12,"help_talk":13,"category":14,"category_talk":15,"matrix":100,"matrix_talk":101,"image":6,"image_talk":7,"project":4,"project_talk":5},"wgSiteName":"AlsaProject","wgFileExtensions":["png","gif","jpg","jpeg"],"wgDBname":"wikidb-alsa","wgFileCanRotate":false,"wgAvailableSkins":{"chick":"Chick","simple":"Simple","nostalgia":"Nostalgia","vector":"Vector","myskin":"MySkin","cologneblue":"CologneBlue","monobook":"MonoBook","modern":"Modern","standard":"Standard"},"wgExtensionAssetsPath":"/main/extensions","wgCookiePrefix":"wikidb-alsa","wgResourceLoaderMaxQueryLength":-1,"wgCaseSensitiveNamespaces":[]});};if(isCompatible()){
document.write("\x3cscript src=\"/main/load.php?debug=false\x26amp;lang=en\x26amp;modules=jquery%2Cmediawiki\x26amp;only=scripts\x26amp;skin=vector\x26amp;version=20120712T144921Z\"\x3e\x3c/script\x3e");}delete isCompatible;;

/* cache key: wikidb-alsa:resourceloader:filter:minify-js:7:7a171f06f4f0e74fa12996a3bb2284d2 */