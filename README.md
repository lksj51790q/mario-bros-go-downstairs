# 瑪莉歐兄弟下樓梯
這是視窗程式設計課程的期末專案。<br>
組員：陳鐿文、蔡辰彥<br>
成品下載：https://drive.google.com/file/d/1-qD_HmM7QyOLGz3rqgrObHuWLPAPltdK/view?usp=sharing<br>
程式語言：C++/CLI<br>
框架：Windows Forms<br>
## 遊戲介紹
### 主介面
主介面可以選擇單人或雙人模式遊玩，將滑鼠游標移至選項時會顯示操作提示。
### 設定
* 音樂與音效的開關控制
* 是否開啟道具模式(平台會隨機出現道具或是踩扁烏龜與蘑菇後掉落)
* 是否開啟無敵模式(老師要求要有無敵模式)
* 難度調整(影響特殊平台出現機率)
### 平台介紹
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/platform_ground.png)人物可以穩定的站在上面<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/platform_log_left.png)人物會向左平移<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/platform_log_right.png)人物會向右平移<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/platform_cloud.png)人物會不斷被彈起<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/platform_eyes_cloud.png)人物踩上去的瞬間平台將會消失<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/platform_mushroom.png)人物在上面時方向操作將會相反<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/platform_spike.png)人物踩上去將會扣血(跳躍再落地也算)<br>
### 道具介紹
同時間最多只能持有一項道具，持有道具時將無法取得新的道具。<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/item_clock.png)使用後地圖停止移動一段時間<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/item_mushroom.png)使用後血量回滿<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/item_speed.png)使用後移動速度提升一段時間<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/item_star.png)使用後一段時間內無敵(若掉落至底部則會瞬移到上方)<br>
### 怪物介紹
碰到怪物會被撞飛，可以從怪物頭頂將其踩扁。<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/mush_stand.png)行動單調，將其踩扁將掉落蘑菇道具<br>
* ![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/final/img/turtle_stand_right.png)會刻意朝角色撞擊，將其踩扁將掉落龜殼道具<br>
### 分數計算
將平台依照難度分類，每單位時間獲得各難度平台出現機率乘上其權重值的分數(各難度平台出現機率會隨遊戲進行而調整)。
### 未來
在經典的小朋友下樓梯遊戲中，雙人模式中的兩人是可以互相阻擋的，甚至是可以站立在對方的頭頂上，這是十分有趣的遊戲要素，但是我們尚未做出這項碰撞機制。

## 程式小細節
Windows Forms並不支援真正的背景透明，因此一般情況下兩圖交疊時會出現圖層被覆蓋的情況。透過覆寫(override)OnPaint函式直接在背景繪圖可以自行控制圖層的上下關係並且讓圖片透明的部分順利作用。(game.h line 2117 ~ 2261)<br>
![image](https://github.com/lksj51790q/mario_bros_go_downstairs/blob/main/override_compare.png)<br>
