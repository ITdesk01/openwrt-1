webpackJsonp([18],{481:function(i,t,s){function a(i){s(589)}var l=s(53)(s(591),s(592),a,"data-v-78ed7045",null);i.exports=l.exports},589:function(i,t,s){var a=s(590);"string"==typeof a&&(a=[[i.i,a,""]]),a.locals&&(i.exports=a.locals);s(462)("fe6931ce",a,!0)},590:function(i,t,s){t=i.exports=s(461)(!1),t.push([i.i,".firewall-container[data-v-78ed7045]{max-width:16rem;padding-top:1.1728rem;margin:0 auto}.firewall-content[data-v-78ed7045]{font-size:.4rem}.firewall-content[data-v-78ed7045],.firewall-item[data-v-78ed7045]{display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-webkit-flex-direction:column;-ms-flex-direction:column;flex-direction:column}.firewall-master-switch[data-v-78ed7045],.firewall-status[data-v-78ed7045]{border-bottom:.013333rem solid hsla(0,0%,74%,.5)}.firewall-status[data-v-78ed7045]{text-align:left;padding:.1rem 0}.firewall-status>span[data-v-78ed7045]{color:#0bc16e}.firewall-item-switch[data-v-78ed7045],.firewall-master-switch[data-v-78ed7045]{height:1.3333rem}.firewall-item-list[data-v-78ed7045],.firewall-item-switch[data-v-78ed7045],.firewall-master-switch[data-v-78ed7045]{display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-pack:justify;-webkit-justify-content:space-between;-ms-flex-pack:justify;justify-content:space-between;-webkit-box-align:center;-webkit-align-items:center;-ms-flex-align:center;align-items:center}.firewall-item-list[data-v-78ed7045]{background-color:#fafafa}.firewall-item-description[data-v-78ed7045]{text-align:left;padding:.2rem .1rem;font-size:.36rem}",""])},591:function(i,t,s){"use strict";Object.defineProperty(t,"__esModule",{value:!0});var a,l=s(174),e=s.n(l);t.default={mounted:function(){this.pageLoading()},data:function(){return{loadingInfo:!0,MasterSwitch:!1,status:"--",malicious:!1,surfingFirewall:!1,familyFirewall:!1,pwdFirewall:!1,resultTip:!1,result:"",resultInfo:""}},methods:(a={pageLoading:function(){var i={requestUrl:"get_firewall_status",method:"get"},t=this;this.$ajax({data:i}).then(function(i){t.loadingInfo=!1,0==i.data.errorcode&&t.firewallstatus(i.data.data)}).catch(function(i){console.log(i)})},beforeRouteLeave:function(i,t,s){this.destroyed()},firewallstatus:function(i){var t=0;1==i.url_firewall?(this.malicious=!0,t++):this.malicious=!1,1==i.dns_hijack_firewall?(this.surfingFirewall=!0,t++):this.surfingFirewall=!1,1==i.family_firewall?(this.familyFirewall=!0,t++):this.familyFirewall=!1,1==i.password_firewall?(this.pwdFirewall=!0,t++):this.pwdFirewall=!1,4==t?(this.MasterSwitch=!0,this.status="已全部开启"):this.status=0==t?"已全部关闭":"部分已开启"},back:function(){this.$router.push("home")},maliciousChecked:function(){this.malicious=!this.malicious,this.oneswitch()},pwdFirewallChecked:function(){this.pwdfirewallChecked=!this.pwdfirewallChecked,this.oneswitch()},surfingFirewallChecked:function(){this.surfingFirewall=!this.surfingFirewall,this.oneswitch()},familyFirewallChecked:function(){this.familyFirewall=!this.familyFirewall,this.oneswitch()}},e.a(a,"pwdFirewallChecked",function(){this.pwdFirewall=!this.pwdFirewall,this.oneswitch()}),e.a(a,"oneswitch",function(){this.resultShow(-1,-1);var i={data:{url_firewall:1==this.malicious?1:0,dns_hijack_firewall:1==this.surfingFirewall?1:0,family_firewall:1==this.familyFirewall?1:0,password_firewall:1==this.pwdFirewall?1:0},requestUrl:"set_firewall_status",method:"post"};this.firewallswitch(i)}),e.a(a,"MasterChecked",function(){if(this.resultShow(-1,-1),this.MasterSwitch=!this.MasterSwitch,this.MasterSwitch){this.malicious=this.surfingFirewall=this.familyFirewall=this.pwdFirewall=!0;var i={data:{url_firewall:1,dns_hijack_firewall:1,family_firewall:1,password_firewall:1},requestUrl:"set_firewall_status",method:"post"}}else{this.malicious=this.surfingFirewall=this.familyFirewall=this.pwdFirewall=!1;var i={data:{url_firewall:0,dns_hijack_firewall:0,family_firewall:0,password_firewall:0},requestUrl:"set_firewall_status",method:"post"}}this.firewallswitch(i)}),e.a(a,"firewallswitch",function(i){this.resultShow(-1,-1);var t=this;this.$ajax({data:i}).then(function(i){t.savedisabled=!1,0==i.data.errorcode?(t.resultShow(1,"保存成功"),t.pageLoading()):t.error_msg(i.data)}).catch(function(i){t.resultShow(0,"网络异常，请检查")})}),a)}},592:function(i,t){i.exports={render:function(){var i=this,t=i.$createElement,s=i._self._c||t;return s("div",{staticClass:"firewall-container container"},[s("header",{staticClass:"header"},[s("span",{staticClass:"back-icon",on:{click:function(t){i.back()}}}),i._v(" "),s("span",{staticClass:"theme"},[i._v("路由器防火墙")])]),i._v(" "),i.loadingInfo?s("loadingInfo",{staticClass:"loadinginfo"}):i._e(),i._v(" "),i.loadingInfo?i._e():s("div",{staticClass:"firewall-content"},[s("div",{staticClass:"firewall-master-switch"},[s("span",[i._v("总开关")]),i._v(" "),s("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:i.MasterSwitch}}),i._v(" "),s("span",{staticClass:"switch-icon",on:{click:function(t){i.MasterChecked()}}})]),i._v(" "),s("div",{staticClass:"firewall-status"},[s("span",[i._v(i._s(i.status))])]),i._v(" "),s("div",{staticClass:"firewall-item"},[s("div",{staticClass:"firewall-item-switch"},[s("span",[i._v("恶意网址防火墙")]),i._v(" "),s("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:i.malicious}}),i._v(" "),s("span",{staticClass:"switch-icon",on:{click:function(t){i.maliciousChecked()}}})]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("阻断挂马网站")]),i._v(" "),i.malicious?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("阻断篡改首页等网址")]),i._v(" "),i.malicious?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("阻断钓鱼、欺诈网址")]),i._v(" "),i.malicious?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("阻断恶意软件下载网址")]),i._v(" "),i.malicious?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("阻断木马和下载者网址")]),i._v(" "),i.malicious?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])])]),i._v(" "),s("div",{staticClass:"firewall-item"},[s("div",{staticClass:"firewall-item-switch"},[s("span",[i._v("上网劫持防火墙")]),i._v(" "),s("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:i.surfingFirewall}}),i._v(" "),s("span",{staticClass:"switch-icon",on:{click:function(t){i.surfingFirewallChecked()}}})]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("防止恶意广告弹出")]),i._v(" "),i.surfingFirewall?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("防止被劫持到钓鱼网站")]),i._v(" "),i.surfingFirewall?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("防止被劫持到挂马网站")]),i._v(" "),i.surfingFirewall?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])])]),i._v(" "),s("div",{staticClass:"firewall-item"},[s("div",{staticClass:"firewall-item-switch"},[s("span",[i._v("家庭网络防火墙")]),i._v(" "),s("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:i.familyFirewall}}),i._v(" "),s("span",{staticClass:"switch-icon",on:{click:function(t){i.familyFirewallChecked()}}})]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("阻止APP断网掉线攻击")]),i._v(" "),i.familyFirewall?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("防止被恶意限速")]),i._v(" "),i.familyFirewall?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])])]),i._v(" "),s("div",{staticClass:"firewall-item"},[s("div",{staticClass:"firewall-item-switch"},[s("span",[i._v("密码安全防火墙")]),i._v(" "),s("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:i.pwdFirewall}}),i._v(" "),s("span",{staticClass:"switch-icon",on:{click:function(t){i.pwdFirewallChecked()}}})]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("wifi密码强度")]),i._v(" "),i.pwdFirewall?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])]),i._v(" "),s("div",{staticClass:"firewall-item-list"},[s("span",{staticClass:"firewall-item-description"},[i._v("管理员密码强度")]),i._v(" "),i.pwdFirewall?s("span",[i._v("保护中")]):s("span",[i._v("未开启")])])])]),i._v(" "),s("resultshow",{attrs:{resultTip:i.resultTip,result:i.result,resultInfo:i.resultInfo}})],1)},staticRenderFns:[]}}});