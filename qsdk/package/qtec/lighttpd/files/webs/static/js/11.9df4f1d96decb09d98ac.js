webpackJsonp([11],{469:function(e,t,a){function i(e){a(536)}var s=a(53)(a(538),a(539),i,"data-v-43e626c6",null);e.exports=s.exports},536:function(e,t,a){var i=a(537);"string"==typeof i&&(i=[[e.i,i,""]]),i.locals&&(e.exports=i.locals);a(462)("98da65e6",i,!0)},537:function(e,t,a){t=e.exports=a(461)(!1),t.push([e.i,".wifi-setting-container[data-v-43e626c6]{max-width:16rem;padding-top:1.1728rem;margin:0 auto}input[data-v-43e626c6]{text-align:right}select[data-v-43e626c6]{width:auto}.high-speed[data-v-43e626c6]{margin-top:.3rem;border-top:.013333rem solid hsla(0,0%,74%,.5)}.form-item[data-v-43e626c6]{display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-justify-content:space-between;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;-webkit-box-align:center;-webkit-align-items:center;-ms-flex-align:center;align-items:center;height:1.3333rem;font-size:.4rem;border-bottom:.013333rem solid hsla(0,0%,74%,.5)}.save-success[data-v-43e626c6]{height:100%;-webkit-box-align:center;-webkit-align-items:center;-ms-flex-align:center;align-items:center;padding:0 .42rem}.save-success[data-v-43e626c6],.success-info[data-v-43e626c6]{width:100%;display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-webkit-flex-direction:column;-ms-flex-direction:column;flex-direction:column;-webkit-box-pack:center;-webkit-justify-content:center;-ms-flex-pack:center;justify-content:center;margin-top:-1.173333rem}.save-icon[data-v-43e626c6]{text-align:center}.success-info img[data-v-43e626c6]{height:1.4rem}.success-info>span[data-v-43e626c6]{font-size:.42rem;line-height:.64rem;padding:.1rem 0;word-break:break-all}.reload-btn[data-v-43e626c6]{display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-webkit-flex-direction:column;-ms-flex-direction:column;flex-direction:column;-webkit-box-pack:center;-webkit-justify-content:center;-ms-flex-pack:center;justify-content:center;-webkit-box-align:center;-webkit-align-items:center;-ms-flex-align:center;align-items:center;margin-top:3rem}.reload-btn>span[data-v-43e626c6]{font-size:.36rem;margin-bottom:.3rem}.reload-btn>button[data-v-43e626c6]{width:6.6rem;padding:.24rem 0;text-align:center;background-color:#179cf3;color:#fff}",""])},538:function(e,t,a){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.default={mounted:function(){this.pageLoading()},data:function(){return{disabled:!0,loadingInfo:!0,normalSettingChecked:!1,SpeedSettingChecked:!1,normalShow:!1,speedShow:!1,normalencrypt:"psk-mixed",showNormalPassword:!1,showSpeedPassword:!1,normalbandwidth:"0",normalnetworkmode:"14",normalwirelwsschannel:"auto",hideNormalChecked:!1,hideSpeedChecked:!1,normalName:"",normalPwd:"********",normalpwdstatus:0,speedName:"",speedencrypt:"psk-mixed",speedPwd:"********",speedpwdstatus:0,speedbandwidth:"0",speednetworkmode:"14",speedwirelesschannel:"auto",saveShow:!1,savenormalssid:"",savespeedssid:"",wificlose:!1,tipShow:!1,tip:"",resultTip:!1,result:"",resultInfo:"",encryptSelects:[{value:"none",text:"不加密"},{value:"psk",text:"WPA-PSK"},{value:"psk2",text:"WPA2-PSK"},{value:"psk-mixed",text:"WPA-PSK/WPA2-PSK混合加密"}],bandwidthSelects:[{value:"0",text:"自动"},{value:"1",text:"20MHZ"},{value:"2",text:"40MHZ"}],speedbandwidthSelects:[{value:"0",text:"自动"},{value:"1",text:"20MHZ"},{value:"2",text:"40MHZ"},{value:"3",text:"80MHZ"}],networkmodeSelects:[{value:"0",text:"802.11b/g"},{value:"1",text:"802.11b"},{value:"2",text:"802.11a"},{value:"4",text:"802.11g"},{value:"7",text:"802.11g/n"},{value:"8",text:"802.11a/n"},{value:"9",text:"802.11b/g/n"},{value:"14",text:"802.11a/an/ac"},{value:"15",text:"802.11an/ac"}],wirelessnormalchannelSelects:[{value:"auto",text:"自动"},{value:"1",text:"信道1"},{value:"2",text:"信道2"},{value:"3",text:"信道3"},{value:"4",text:"信道4"},{value:"5",text:"信道5"},{value:"6",text:"信道6"},{value:"7",text:"信道7"},{value:"8",text:"信道8"},{value:"9",text:"信道9"},{value:"10",text:"信道10"},{value:"11",text:"信道11"},{value:"12",text:"信道12"},{value:"13",text:"信道13"}],wirelessspeedchannelSelects:[{value:"auto",text:"自动"},{value:"36",text:"信道36"},{value:"40",text:"信道40"},{value:"44",text:"信道44"},{value:"48",text:"信道48"},{value:"52",text:"信道52"},{value:"56",text:"信道56"},{value:"60",text:"信道60"},{value:"64",text:"信道64"},{value:"149",text:"信道149"},{value:"153",text:"信道153"},{value:"157",text:"信道157"},{value:"161",text:"信道161"},{value:"165",text:"信道165"}]}},methods:{pageLoading:function(){var e={requestUrl:"get_wireless_cfg",method:"get"},t=this;this.$ajax({data:e}).then(function(e){t.disabled=!1,0==e.data.errorcode?(0==e.data.data.disabled1&&(t.normalSettingChecked=!0,t.normalShow=!0),1==e.data.data.hidden1&&(t.hideNormalChecked=!0),t.normalName=e.data.data.ssid1,t.normalencrypt=e.data.data.encryption1,t.normalbandwidth=e.data.data.bandwith1,t.normalnetworkmode=e.data.data.wifimode1,t.normalwirelwsschannel=e.data.data.channel1,0==e.data.data.disabled2&&(t.SpeedSettingChecked=!0,t.speedShow=!0),1==e.data.data.hidden2&&(t.hideSpeedChecked=!0),t.speedName=e.data.data.ssid2,t.speedencrypt=e.data.data.encryption2,t.speedbandwidth=e.data.data.bandwith2,t.speednetworkmode=e.data.data.wifimode2,t.speedwirelesschannel=e.data.data.channel2,t.loadingInfo=!1):t.error_msg(e.data)}).catch(function(e){t.resultShow(0,"请确保wifi连接状态正常后刷新页面")})},beforeRouteLeave:function(e,t,a){this.destroyed()},back:function(){this.$router.push("home")},normalfocus:function(){0==this.normalpwdstatus&&(this.normalPwd="")},normalblur:function(){0==this.normalPwd.length?(this.normalPwd="********",this.normalpwdstatus=0):this.normalpwdstatus=1},speedfocus:function(){this.speedPwd=""},speedblur:function(){0==this.speedPwd.length?(this.speedPwd="********",this.speedpwdstatus=0):this.speedpwdstatus=1},reload:function(){location.reload()},save:function(){var e,t,a,i,s=/^.{8,63}$/;if(1==this.normalSettingChecked){if(!this.normalName)return void this.resultShow(0,"2.4Gwifi名称或密码不能为空");if(this.countnums(this.normalName)>32)return void this.resultShow(0,"请输入1-32位2.4Gwifi名称");if(this.normalPwd){if(!s.test(this.normalPwd))return void this.resultShow(0,"请输入8-63位2.4Gwifi密码");if(-1==this.cn_test(this.normalPwd))return void this.resultShow(0,"2.4Gwifi密码不支持中文字符")}e="0"}else e="1";a=1==this.hideNormalChecked?"1":"0";var n=this.normalencrypt,l=this.normalbandwidth,o=this.normalnetworkmode,d=this.normalwirelwsschannel;if(""==n||""==l||""==o||""==d)return void this.resultShow(0,"2.4Gwifi信息设置不完整");if(1==this.SpeedSettingChecked){if(!this.speedName)return void this.resultShow(0,"5Gwifi名称或密码不能为空");if(this.countnums(this.speedName)>32)return void this.resultShow(0,"请输入1-32位5Gwifi名称");if(this.speedPwd){if(!s.test(this.speedPwd))return void this.resultShow(0,"请输入8-63位5Gwifi密码");if(-1==this.cn_test(this.speedPwd))return void this.resultShow(0,"5Gwifi密码不支持中文字符")}t="0"}else t="1";i=1==this.hideSpeedChecked?"1":"0";var r=this.speedencrypt,c=this.speedbandwidth,u=this.speednetworkmode,v=this.speedwirelesschannel;if(""==r||""==c||""==u||""==v)return void this.resultShow(0,"5Gwifi信息设置不完整");this.resultShow(-1,-1),this.disabled=!0;var m="",p="";if(1==this.normalpwdstatus||1==this.speedpwdstatus){var h={requestUrl:"getkeycfg",method:"get"},w=this.normalPwd,f=this.speedPwd,b=this;this.$ajax({data:h}).then(function(s){if(0==s.data.errorcode){var h=new JSEncrypt,_=s.data.data.rand_key;h.setPublicKey(_),1==b.normalpwdstatus&&(m=h.encrypt(w)),1==b.speedpwdstatus&&(p=h.encrypt(f));var x={data:{disabled1:e,ssid1:b.normalName,key1:m,hidden1:a,encryption1:n,bandwith1:l,wifimode1:o,channel1:d,disabled2:t,ssid2:b.speedName,key2:p,hidden2:i,encryption2:r,bandwith2:c,wifimode2:u,channel2:v},requestUrl:"set_wireless_cfg",method:"put"};b.submit(x)}else b.disabled=!1,b.resultShow(-2),b.error_msg(s.data)}).catch(function(e){b.disabled=!1,b.resultShow(0,"网络异常，请检查")})}else{var h={data:{disabled1:e,ssid1:this.normalName,key1:m,hidden1:a,encryption1:n,bandwith1:l,wifimode1:o,channel1:d,disabled2:t,ssid2:this.speedName,key2:p,hidden2:i,encryption2:r,bandwith2:c,wifimode2:u,channel2:v},requestUrl:"set_wireless_cfg",method:"put"};this.submit(h)}},submit:function(e){var t=this;this.$ajax({data:e}).then(function(a){t.disabled=!1,0==a.data.errorcode?(t.resultShow(-2),"1"==e.data.disabled1&&(t.normalName="已关闭，不支持5Gwifi的设备将无法连接"),t.savenormalssid=t.normalName,"1"==e.data.disabled2&&(t.speedName="已关闭"),"1"==e.data.disabled1&&"1"==e.data.disabled2&&(t.wificlose=!0),t.savespeedssid=t.speedName,t.saveShow=!0):(t.resultShow(-2),t.error_msg(a.data))}).catch(function(e){t.disabled=!1,t.resultShow(0,"网络异常，请检查")})},settingShow:function(e){"nomal"==e&&(this.normalSettingChecked=!this.normalSettingChecked,this.normalShow=!this.normalShow),"speed"==e&&(this.SpeedSettingChecked=!this.SpeedSettingChecked,this.speedShow=!this.speedShow)},hideWifi:function(e){"nomal"==e&&(this.hideNormalChecked=!this.hideNormalChecked),"speed"==e&&(this.hideSpeedChecked=!this.hideSpeedChecked)},tipClose:function(){this.tipShow=!1}}}},539:function(e,t,a){e.exports={render:function(){var e=this,t=e.$createElement,i=e._self._c||t;return i("div",{staticClass:"wifi-setting-container container"},[e.saveShow?e._e():i("header",{staticClass:"header"},[i("span",{staticClass:"back-icon",on:{click:function(t){e.back()}}}),e._v(" "),i("span",{staticClass:"theme"},[e._v("wifi设置")]),e._v(" "),i("div",{staticClass:"save"},[i("button",{attrs:{type:"button",disabled:e.disabled},on:{click:function(t){e.save()}}},[e._v("保存")])])]),e._v(" "),e.loadingInfo?i("loadingInfo",{staticClass:"loadinginfo"}):e._e(),e._v(" "),e.loadingInfo||e.saveShow?e._e():i("div",{staticClass:"content"},[i("div",{staticClass:"nomal"},[i("div",{staticClass:"switch-item form-item"},[i("label",{staticClass:"description-main"},[e._v("2.4G wifi")]),e._v(" "),i("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:e.normalSettingChecked}}),e._v(" "),i("span",{staticClass:"switch-icon",on:{click:function(t){e.settingShow("nomal")}}})]),e._v(" "),i("div",{directives:[{name:"show",rawName:"v-show",value:e.normalShow,expression:"normalShow"}],staticClass:"nomal-setting"},[i("div",{staticClass:"hide-wifi form-item"},[i("label",[e._v("隐藏2.4G wifi")]),e._v(" "),i("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:e.hideNormalChecked}}),e._v(" "),i("span",{staticClass:"switch-icon",on:{click:function(t){e.hideWifi("nomal")}}})]),e._v(" "),i("div",{staticClass:"wifi-name-setting form-item"},[i("label",[e._v("wifi名称")]),e._v(" "),i("input",{directives:[{name:"model",rawName:"v-model",value:e.normalName,expression:"normalName"}],attrs:{type:"text",maxlength:"32",placeholder:"请输入2.4G wifi名称",autocomplete:"off"},domProps:{value:e.normalName},on:{input:function(t){t.target.composing||(e.normalName=t.target.value)}}})]),e._v(" "),i("div",{staticClass:"encrypt-mode-setting form-item"},[i("label",[e._v("加密方式")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.normalencrypt,expression:"normalencrypt"}],staticClass:"normal-encrypt-mode",on:{change:function(t){var a=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.normalencrypt=t.target.multiple?a:a[0]}}},e._l(e.encryptSelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(a){e.$set(t,"value",a)},expression:"option.value"}},[e._v(e._s(t.text))])}))]),e._v(" "),i("div",{staticClass:"wifi-pwd-setting form-item"},[i("label",[e._v("wifi密码")]),e._v(" "),i("input",{directives:[{name:"model",rawName:"v-model",value:e.normalPwd,expression:"normalPwd"}],staticClass:"wifi-pwd",attrs:{type:"password",maxlength:"63",placeholder:"请输入2.4G wifi密码",autocomplete:"off"},domProps:{value:e.normalPwd},on:{focus:function(t){e.normalfocus()},blur:function(t){e.normalblur()},input:function(t){t.target.composing||(e.normalPwd=t.target.value)}}})]),e._v(" "),i("div",{staticClass:"form-item"},[i("label",[e._v("频道带宽")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.normalbandwidth,expression:"normalbandwidth"}],staticClass:"normal-wifi-band-width",on:{change:function(t){var a=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.normalbandwidth=t.target.multiple?a:a[0]}}},e._l(e.bandwidthSelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(a){e.$set(t,"value",a)},expression:"option.value"}},[e._v(e._s(t.text))])}))]),e._v(" "),i("div",{staticClass:"form-item"},[i("label",[e._v("无线模式")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.normalnetworkmode,expression:"normalnetworkmode"}],staticClass:"normal-wifi-network-mode",on:{change:function(t){var a=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.normalnetworkmode=t.target.multiple?a:a[0]}}},e._l(e.networkmodeSelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(a){e.$set(t,"value",a)},expression:"option.value"}},[e._v(e._s(t.text))])}))]),e._v(" "),i("div",{staticClass:"form-item"},[i("label",[e._v("无线信道")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.normalwirelwsschannel,expression:"normalwirelwsschannel"}],staticClass:"normal-wifi-wireless-channel",on:{change:function(t){var a=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.normalwirelwsschannel=t.target.multiple?a:a[0]}}},e._l(e.wirelessnormalchannelSelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(a){e.$set(t,"value",a)},expression:"option.value"}},[e._v(e._s(t.text))])}))])])]),e._v(" "),i("div",{staticClass:"high-speed"},[i("div",{staticClass:"switch-item form-item"},[i("label",{staticClass:"description-main"},[e._v("5G wifi")]),e._v(" "),i("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:e.SpeedSettingChecked}}),e._v(" "),i("span",{staticClass:"switch-icon",on:{click:function(t){e.settingShow("speed")}}})]),e._v(" "),i("div",{directives:[{name:"show",rawName:"v-show",value:e.speedShow,expression:"speedShow"}],staticClass:"high-speed-setting"},[i("div",{staticClass:"hide-wifi form-item"},[i("label",[e._v("隐藏5G wifi")]),e._v(" "),i("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:e.hideSpeedChecked}}),e._v(" "),i("span",{staticClass:"switch-icon",on:{click:function(t){e.hideWifi("speed")}}})]),e._v(" "),i("div",{staticClass:"wifi-name-setting form-item"},[i("label",[e._v("wifi名称")]),e._v(" "),i("input",{directives:[{name:"model",rawName:"v-model",value:e.speedName,expression:"speedName"}],attrs:{type:"text",maxlength:"32",placeholder:"请输入5G wifi名称"},domProps:{value:e.speedName},on:{input:function(t){t.target.composing||(e.speedName=t.target.value)}}})]),e._v(" "),i("div",{staticClass:"encrypt-mode-setting form-item"},[i("label",[e._v("加密方式")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.speedencrypt,expression:"speedencrypt"}],staticClass:"speed-encrypt-mode",on:{change:function(t){var a=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.speedencrypt=t.target.multiple?a:a[0]}}},e._l(e.encryptSelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(a){e.$set(t,"value",a)},expression:"option.value"}},[e._v(e._s(t.text))])}))]),e._v(" "),i("div",{staticClass:"wifi-pwd-setting form-item"},[i("label",[e._v("wifi密码")]),e._v(" "),i("input",{directives:[{name:"model",rawName:"v-model",value:e.speedPwd,expression:"speedPwd"}],staticClass:"wifi-pwd",attrs:{type:"password",maxlength:"63",placeholder:"请输入5G wifi密码"},domProps:{value:e.speedPwd},on:{focus:function(t){e.speedfocus()},blur:function(t){e.speedblur()},input:function(t){t.target.composing||(e.speedPwd=t.target.value)}}})]),e._v(" "),i("div",{staticClass:"wifi-band-width-setting form-item"},[i("label",[e._v("频道带宽")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.speedbandwidth,expression:"speedbandwidth"}],staticClass:"speed-wifi-band-width",on:{change:function(t){var a=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.speedbandwidth=t.target.multiple?a:a[0]}}},e._l(e.speedbandwidthSelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(a){e.$set(t,"value",a)},expression:"option.value"}},[e._v(e._s(t.text))])}))]),e._v(" "),i("div",{staticClass:"form-item"},[i("label",[e._v("无线模式")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.speednetworkmode,expression:"speednetworkmode"}],staticClass:"speed-wifi-network-mode",on:{change:function(t){var a=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.speednetworkmode=t.target.multiple?a:a[0]}}},e._l(e.networkmodeSelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(a){e.$set(t,"value",a)},expression:"option.value"}},[e._v(e._s(t.text))])}))]),e._v(" "),i("div",{staticClass:"form-item"},[i("label",[e._v("无线信道")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.speedwirelesschannel,expression:"speedwirelesschannel"}],staticClass:"speed-wifi-wireless-channel",on:{change:function(t){var a=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.speedwirelesschannel=t.target.multiple?a:a[0]}}},e._l(e.wirelessspeedchannelSelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(a){e.$set(t,"value",a)},expression:"option.value"}},[e._v(e._s(t.text))])}))])])])]),e._v(" "),i("transition",{attrs:{"enter-active-class":"fadeIn"}},[e.saveShow?i("div",{staticClass:"save-success"},[i("div",{staticClass:"success-info"},[i("div",{staticClass:"save-icon"},[i("img",{attrs:{src:a(173),alt:"success"}})]),e._v(" "),i("span",[e._v("wifi设置成功")]),e._v(" "),e.wificlose?e._e():i("span",[e._v("请等待wifi重启后，重新连接以下wifi")]),e._v(" "),e.wificlose?e._e():i("span",[e._v("2.4G:"+e._s(e.savenormalssid))]),e._v(" "),e.wificlose?e._e():i("span",[e._v("5G:"+e._s(e.savespeedssid))]),e._v(" "),e.wificlose?i("span",[e._v("wifi已关闭")]):e._e(),e._v(" "),e.wificlose?i("span",[e._v("通过有线连设备wifi管理页面可重新开启")]):e._e()]),e._v(" "),i("div",{staticClass:"reload-btn"},[e.wificlose?e._e():i("span",[e._v("wifi连接成功后，点击确定按钮刷新页面")]),e._v(" "),e.wificlose?e._e():i("button",{attrs:{type:"button"},on:{click:function(t){e.reload()}}},[e._v("确定")])])]):e._e()]),e._v(" "),i("transition",{attrs:{"enter-active-class":"fadeIn","leave-active-class":"animated fadeOut"}},[e.tipShow?i("div",{staticClass:"loading"},[i("div",{staticClass:"tip-box"},[i("span",{staticClass:"tip-header"},[e._v("提示")]),e._v(" "),i("span",{staticClass:"tip-main"},[e._v(e._s(e.tip))])]),e._v(" "),i("div",{staticClass:"tip-btns"},[i("button",{staticClass:"cancel",attrs:{disabled:!e.tipShow,type:"button"},on:{click:function(t){e.cancel()}}},[e._v("取消")]),e._v(" "),i("button",{attrs:{type:"button",disabled:!e.tipShow},on:{click:function(t){e.confirm()}}},[e._v("确认")])])]):e._e()]),e._v(" "),i("resultshow",{attrs:{resultTip:e.resultTip,result:e.result,resultInfo:e.resultInfo}})],1)},staticRenderFns:[]}}});