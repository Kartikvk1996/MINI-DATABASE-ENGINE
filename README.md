# MINI-DATABASE-ENGINE (still under development)
mini database engine written in C

<h2>Supports query such as</h2>  <br/><b>1. select </b> Selects all the data from table<br/>
<b>2. desc </b> Describes the table info<br/>
<b>3. show </b> Shows all table info.<br/>
<b>4. create</b> Creates new table -- constraint is only primary_key is supported and write primary key as <b>'primary_key'</b>.<br/>
<b>5. insert</b> inserts value to the table<br/><br/>

<h2>datatype supported</h2><br/> int , float , double ,char(supported for string upto 255 charecters only . specify only char to store string)<br/><br/><p style="color:green">[12-5-17] Removed segmentation fault error on insertion of string. <br>[3-8-17] added locking of file which is in use, to maintain consistency.</p><br><br>

<h2>Todo</h2><br/>
<b>1. </b> 'where' clause for select query.<br/>
<b>2. </b> update , delete and drop command.<br/>
<b>3. </b> indexing on non-prime attributes (clustered indexing) (indexing at present is done only to primary_key).<br/>
<br/><br/>

![screenshot 33](https://cloud.githubusercontent.com/assets/21128320/25394355/76dc9fea-29fb-11e7-9f52-68fa73d6210e.png)<br/><br/>
![screenshot 34](https://cloud.githubusercontent.com/assets/21128320/25394354/76d9a1dc-29fb-11e7-8a1d-40e9ac6f0276.png)<br/><br/>
![screenshot 29](https://cloud.githubusercontent.com/assets/21128320/25394356/76e0ba80-29fb-11e7-859e-cc1b19d371a8.png)<br/><br/>
![screenshot 35](https://cloud.githubusercontent.com/assets/21128320/25395096/9675ad9a-29fd-11e7-90d1-9eb92a428f29.png)<br/><br/>
