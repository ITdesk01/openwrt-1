webpackJsonp([21],{477:function(e,t,i){function a(e){i(570)}var o=i(53)(i(572),i(573),a,"data-v-b2dc9580",null);e.exports=o.exports},570:function(e,t,i){var a=i(571);"string"==typeof a&&(a=[[e.i,a,""]]),a.locals&&(e.exports=a.locals);i(462)("86194162",a,!0)},571:function(e,t,i){t=e.exports=i(461)(!1),t.push([e.i,".qos-container[data-v-b2dc9580]{max-width:16rem;margin:0 auto;padding-top:1.173333rem}.qos-settings[data-v-b2dc9580]{display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-webkit-flex-direction:column;-ms-flex-direction:column;flex-direction:column;font-size:.4rem}.qos-switch[data-v-b2dc9580]{-webkit-box-align:center;-webkit-align-items:center;-ms-flex-align:center;align-items:center;padding:.3535rem .1rem}.qos-priority[data-v-b2dc9580],.qos-switch[data-v-b2dc9580]{display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-pack:justify;-webkit-justify-content:space-between;-ms-flex-pack:justify;justify-content:space-between;border-bottom:.013333rem solid hsla(0,0%,74%,.5)}.qos-priority[data-v-b2dc9580]{padding:.2rem .1rem}.qos-settings-content[data-v-b2dc9580]{display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-webkit-flex-direction:column;-ms-flex-direction:column;flex-direction:column;text-align:left;border-bottom:.013333rem solid hsla(0,0%,74%,.5)}.qos-settings-content>span[data-v-b2dc9580]{padding:.1rem}.download-bandwidth[data-v-b2dc9580],.upload-bandwidth[data-v-b2dc9580]{padding:.2rem .1rem;border-top:.013333rem solid hsla(0,0%,74%,.5);display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-pack:justify;-webkit-justify-content:space-between;-ms-flex-pack:justify;justify-content:space-between}.speed-input[data-v-b2dc9580]{display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-box-align:center;-webkit-align-items:center;-ms-flex-align:center;align-items:center}.download-bandwidth input[data-v-b2dc9580],.upload-bandwidth input[data-v-b2dc9580]{text-align:right;padding:.1rem;max-width:3rem;border-radius:.083333rem}.reguler[data-v-b2dc9580]{text-align:right}",""])},572:function(e,t,i){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.default={mounted:function(){this.pageLoading()},data:function(){return{loadingInfo:!0,disabled:!0,qosSwitchChecked:!1,priority:0,prioritySelects:[{value:0,text:"自动模式"},{value:1,text:"游戏优先"},{value:2,text:"网页优先"},{value:3,text:"视频优先"}],uploadSpeed:0,downloadSpeed:0,resultTip:!1,result:"",resultInfo:""}},methods:{pageLoading:function(){var e={requestUrl:"proc_qos_cfg",method:"get"},t=this;this.$ajax({data:e}).then(function(e){t.disabled=!1,0==e.data.errorcode?(1==e.data.data.enabled?t.qosSwitchChecked=!0:t.qosSwitchChecked=!1,t.priority=e.data.data.qosmode,t.uploadSpeedtmp=e.data.data.upload/1024,t.uploadSpeed=t.uploadSpeedtmp.toFixed(2),t.downloadSpeedtmp=e.data.data.download/1024,t.downloadSpeed=t.downloadSpeedtmp.toFixed(2),t.loadingInfo=!1):t.error_msg(e.data)}).catch(function(e){t.resultShow(0,"网络异常，请检查")})},beforeRouteLeave:function(e,t,i){this.destroyed()},back:function(){this.$router.push("home")},check:function(e,t){t>1e3&&(0==e&&(this.downloadSpeed=1e3),1==e&&(this.uploadSpeed=1e3))},save:function(){if(this.qosSwitchChecked&&0==this.priority.length)return void this.resultShow(0,"Qos模式未选择");if(0==this.downloadSpeed.length)return void this.resultShow(0,"下行带宽不能为空");if(0==this.uploadSpeed.length)return void this.resultShow(0,"上行带宽不能为空");var e=/(^[0]{1}[\.]{0,1}[0-9]{0,2}$)|(^[1-9]{1}[0-9]{0,3}[\.]{0,1}[0-9]{0,2}$)/;if(!e.test(this.uploadSpeed)||!e.test(this.downloadSpeed))return void this.resultShow(0,"请输入0-1000以内的数值,最多2位小数");if(this.uploadSpeed<0||this.uploadSpeed>1e3||this.downloadSpeed<0||this.downloadSpeed>1e3)return void this.resultShow(0,"最大值为1000");this.resultShow(-1,-1);var t={data:{qosmode:Number(this.priority),download:Number(1024*this.downloadSpeed),upload:Number(1024*this.uploadSpeed),enabled:1==this.qosSwitchChecked?1:0},requestUrl:"proc_qos_cfg",method:"put"},i=this;this.$ajax({data:t}).then(function(e){i.disabled=!i.disabled,0==e.data.errorcode?(i.resultShow(1,"保存成功"),i.pageLoading()):i.error_msg(e.data)}).catch(function(e){i.resultShow(0,"网络异常，请检查")})},qosswitchChecked:function(){this.qosSwitchChecked=!this.qosSwitchChecked,this.qosSwitchChecked||(this.uploadSpeed=this.uploadSpeedtmp.toFixed(2),this.downloadSpeed=this.downloadSpeedtmp.toFixed(2))}}}},573:function(e,t){e.exports={render:function(){var e=this,t=e.$createElement,i=e._self._c||t;return i("div",{staticClass:"qos-container container"},[i("header",{staticClass:"header"},[i("span",{staticClass:"back-icon",on:{click:function(t){e.back()}}}),e._v(" "),i("span",{staticClass:"theme"},[e._v("智能宽带")]),e._v(" "),i("div",{staticClass:"save"},[i("button",{attrs:{type:"button",disabled:e.disabled},on:{click:function(t){e.save()}}},[e._v("保存")])])]),e._v(" "),e.loadingInfo?i("loadingInfo",{staticClass:"loadinginfo"}):e._e(),e._v(" "),e.loadingInfo?e._e():i("div",{staticClass:"qos-settings"},[i("div",{staticClass:"qos-switch"},[i("span",[e._v("智能Qos状态：")]),e._v(" "),i("input",{staticClass:"switch-input",attrs:{type:"checkbox"},domProps:{checked:e.qosSwitchChecked}}),e._v(" "),i("span",{staticClass:"switch-icon",on:{click:function(t){e.qosswitchChecked()}}})]),e._v(" "),i("div",{staticClass:"qos-priority"},[i("label",[e._v("按照应用优先级分配")]),e._v(" "),i("select",{directives:[{name:"model",rawName:"v-model",value:e.priority,expression:"priority"}],staticClass:"priority-mode",attrs:{disabled:!e.qosSwitchChecked},on:{change:function(t){var i=Array.prototype.filter.call(t.target.options,function(e){return e.selected}).map(function(e){return"_value"in e?e._value:e.value});e.priority=t.target.multiple?i:i[0]}}},e._l(e.prioritySelects,function(t){return i("option",{domProps:{value:t.value},model:{value:t.value,callback:function(i){e.$set(t,"value",i)},expression:"option.value"}},[e._v(e._s(t.text))])}))]),e._v(" "),i("div",{staticClass:"qos-settings-content"},[i("span",[e._v("带宽设置")]),e._v(" "),i("div",{staticClass:"download-bandwidth"},[i("label",[e._v("下行带宽：")]),e._v(" "),i("div",{staticClass:"speed-input"},[i("input",{directives:[{name:"model",rawName:"v-model",value:e.downloadSpeed,expression:"downloadSpeed"}],attrs:{type:"text",disabled:!e.qosSwitchChecked,maxlength:"7",autocomplete:"off",placeholder:"请输入带宽下行"},domProps:{value:e.downloadSpeed},on:{input:[function(t){t.target.composing||(e.downloadSpeed=t.target.value)},function(t){e.check(0,e.downloadSpeed)}]}}),e._v(" "),i("span",[e._v("Mbps")])])]),e._v(" "),i("div",{staticClass:"upload-bandwidth"},[i("label",[e._v("上行带宽：")]),e._v(" "),i("div",{staticClass:"speed-input"},[i("input",{directives:[{name:"model",rawName:"v-model",value:e.uploadSpeed,expression:"uploadSpeed"}],attrs:{type:"text",disabled:!e.qosSwitchChecked,maxlength:"7",autocomplete:"off",placeholder:"请输入带宽上行"},domProps:{value:e.uploadSpeed},on:{input:[function(t){t.target.composing||(e.uploadSpeed=t.target.value)},function(t){e.check(1,e.uploadSpeed)}]}}),e._v(" "),i("span",[e._v("Mbps")])])])]),e._v(" "),e._m(0,!1,!1)]),e._v(" "),i("resultshow",{attrs:{resultTip:e.resultTip,result:e.result,resultInfo:e.resultInfo}})],1)},staticRenderFns:[function(){var e=this,t=e.$createElement,i=e._self._c||t;return i("div",{staticClass:"reguler"},[i("span",[e._v("* 0代表不限速,最大值位1000,最多2位小数")])])}]}}});