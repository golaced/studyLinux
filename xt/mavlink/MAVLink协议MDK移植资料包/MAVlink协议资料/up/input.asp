<!--#include file="conn.asp"-->


<html>
<head>
<title>协议解析</title>
<meta http-equiv="Content-Type" content="text/html;  charset=gb2312">
<link rel="stylesheet" href="style.css"  type="text/css">
<style type="text/css">
<!--
.STYLE1 {color: #006699}
.STYLE2 {color: #003399}
-->
.main
{
	border-top:1px solid;
	border-bottom:1px solid;
	border-right:1px solid;
	border-radius:10px;
	height:30px;
	}
</style>
</head>
<body background="images/backgr2.jpg">
<table width="100%" border="0" cellspacing="0" cellpadding="0" class="t1">
              <tr bgcolor="#ffc000"> 
                <td class="main" align="center">ID</td>
                <td class="main" align="center">STX</td>
                <td class="main" align="center">LEN</td>
                <td class="main" align="center">SEQ</td>
                <td class="main" align="center">SYS</td>
                <td class="main" align="center">COMP</td>
                <td class="main" align="center">MSG</td>
                <td class="main" align="center">PAYLOAD</td>
                <td class="main" align="center">CKA</td>
                <td class="main" align="center">CKB</td>
              </tr>
     <script>
function del ()  //用于判断记录有没有选中的函数
{
var flag=true;
var temp="";
var  tmp;
if((document.form1.answer.length+"")=="undefined") {tmp=1}else{tmp=document.form1.answer.length}
if (tmp==1){
if (document.form1.answer.checked){
    flag=false;
  temp=document.form1.answer.value
}
}else{
for (i=0;i<document.form1.answer.length;i++) {
if (document.form1.answer[i].checked){
 if (temp==""){
 flag=false;
 temp=document.form1.answer[i].value
 }else{
 flag=false;
 temp = temp +","+ document.form1.answer[i].value
 }
 }
 }
 }
if (flag){ alert("对不起，你还没有选择！")}
else{   name=document.form1.name.value
        //alert(name)
          if (confirm("确实，确定，要删除选中的记录？此举不可恢复，请三思而后点！^_^")){
        window.location="delnews.asp?id=" + temp;
}
}
return !flag;
}
</script>

<script language=Javascript>
function checkall(all)//用于判断全选记录的函数
{
  var a = document.getElementsByName("answer");
  for (var i=0; i<a.length; i++) a[i].checked = all.checked;
}
</script>

	 <%
	 Function HEX_to_BIN(Hex)
Dim i , B
    Hex = UCase(Hex)
    For i = 1 To Len(Hex)
        Select Case Mid(Hex, i, 1)
            Case "0": B = B & "0000"
            Case "1": B = B & "0001"
            Case "2": B = B & "0010"
            Case "3": B = B & "0011"
            Case "4": B = B & "0100"
            Case "5": B = B & "0101"
            Case "6": B = B & "0110"
            Case "7": B = B & "0111"
            Case "8": B = B & "1000"
            Case "9": B = B & "1001"
            Case "A": B = B & "1010"
            Case "B": B = B & "1011"
            Case "C": B = B & "1100"
            Case "D": B = B & "1101"
            Case "E": B = B & "1110"
            Case "F": B = B & "1111"
        End Select
    Next

    While Left(B, 1) = "0"
        B = Right(B, Len(B) - 1)
    Wend

    HEX_to_BIN = B
End Function

function BcH(num)'二进制转十六进制 
BcH=Hex(cDec(num)) 
end function 

function cDec(num)'二进制转十进制 
cDecstr=0 
if len(num)>0 and isnumeric(num) then 
for inum=0 to len(num)-1 
cDecstr=cDecstr+2^inum*cint(mid(num,len(num)-inum,1)) 
next 
end if 
cDec=cDecstr 
end function 
Function sTb(vin) 
        Const adTypeText = 2 
        Dim BytesStream,StringReturn 
        Set BytesStream = Server.CreateObject("ADODB.Stream") 
 With BytesStream 
       .Type = adTypeText 
       .Open 
       .WriteText vin 
       .Position = 0 
       .Charset = "GB2312" 
       .Position = 2 
        StringReturn = .ReadText 
       .Close 
   End With 
Set BytesStream = Nothing 
sTb = StringReturn 
End Function 



   dim i,intPage,page,pre,last,filepath
  set rs = server.CreateObject("adodb.recordset")
   sql="select top 1000 * from cont order by id"

     
      rs.CursorLocation = 3
      rs.Open sql,conn,0,2,1  '这里执行你查询SQL并获得结果记录集
      pre = true
      last = true
      page = trim(Request.QueryString("page"))
      
      
    if not rs.eof then
      
    end if
%> 
<%    
   for i=1 to 1000
     if rs.EOF or rs.BOF then exit for
 
dim mystr,mystr0 
mystr0=rs("Content") 
mystr=split(mystr0,"-") 

'for j=2 to ubound(mystr) 
'response.write mystr(j) 
'next  
  
  
  
  
  
  %> 

                <tr>     
                <td style="border-bottom:1px solid;border-right:1px solid" class="main" align="center"><%=trim(rs("id"))%></td>
                <td style="border-bottom:1px solid;border-right:1px solid;background:#FF9000" align="center"><%=response.write( mystr(0)) %></td>
                <td style="border-bottom:1px solid;border-right:1px solid;background:#00FF61" align="center"><%
				if ubound(mystr) >0 then
				response.write( mystr(1))
				end if %></td>
                <td style="border-bottom:1px solid;border-right:1px solid;background:#5EFF61" align="center"><%
				if ubound(mystr) >1 then
				response.write( mystr(2))
				end if %></td>
                <td style="border-bottom:1px solid;border-right:1px solid;background:#88FF61" align="center"><%
				if ubound(mystr) >2 then
				response.write( mystr(3))
				end if %></td>
				<td style="border-bottom:1px solid;border-right:1px solid;background:#A8FF61" align="center"><%
				if ubound(mystr) >3 then
				response.write( mystr(4))
				end if %></td>
                <td style="border-bottom:1px solid;border-right:1px solid;background:#38CCFF" align="center"><%
				if ubound(mystr) >4 then
				response.write( mystr(5)&"(Hex)")
				conn.CursorLocation=3
					  set rst = server.CreateObject("adodb.recordset")
   sqlt="select * from trans where [HEX] like '"&mystr(5)&"'"
dim dslkd
      rst.Open sqlt,conn,1,1  '这里执行你查询SQL并获得结果记录集
	  if not rst.eof and not rst.bof then
	  	dslkd=		rst("SJZ")	
					response.Write("<br>#")
					response.Write(rst("SJZ"))
					response.Write("【")
					response.Write(rst("CHN"))
					response.Write("】")
	end if
					

					rst.close
				
				
				
				end if %></td>
                <td style="border-bottom:1px solid;border-right:1px solid" align="left">
				<%
				if ubound(mystr) >5 then
				response.Write("<strong>原始16进制数据</strong>")
				for j=6 to int(ubound(mystr))-3
				response.write mystr(j)&"-"
				next   
				response.write mystr(int(ubound(mystr))-2)
				response.Write("<br>")
				'--------------------------------
				response.Write("<strong>转为2进制</strong>")
				for j=6 to int(ubound(mystr))-2
				response.write right("00000000" & HEX_to_BIN(mystr(j)),8)
				response.write "-"
				next   
				response.Write("<br>")
				'--------------------------------
				'response.Write("<strong>转为2进制</strong>")
				dim allbin
				allbin=""
				for j=6 to int(ubound(mystr))-2
				allbin=allbin&right("00000000" & HEX_to_BIN(mystr(j)),8)
				next   
				'response.Write(allbin&"<br>")
				'--------------------------------
					set rslk = server.CreateObject("adodb.recordset")
					sqllk="select * from link where [SJZ] like '"&dslkd&"'"
					
				
					rslk.Open sqllk,conn,1,1  '这里执行你查询SQL并获得结果记录集
					if not rslk.eof or not rslk.bof then
						

						
						
						
						
						
						dim n
						n=1
						do while not rslk.eof and not rslk.bof 
						response.Write("【"&rslk("Memo")&"】"&rslk("Type")&"["&rslk("len2")&"]")
						
						'response.Write	mid(allbin,n,rslk("len2"))
						
						if rslk("Type") = "uint" then
						response.Write("值:"&int(cDec(mid(allbin,n,rslk("len2")))))
						elseif rslk("Type") = "char" then
						response.Write("值:"&(cDec(mid(allbin,n,rslk("len2")))))
						elseif rslk("Type") = "int" then
						response.Write("值:"&int(cDec(mid(allbin,n,rslk("len2")))))
						elseif rslk("Type") = "float" then
						response.Write("值:"&(cDec(mid(allbin,n,rslk("len2")))))
						end if
						
						n=n+rslk("len2")
							rslk.movenext
							
						loop	
					
						rslk.close
						response.Write("|")
					else
						for j=6 to int(ubound(mystr))-3
						response.write mystr(j)&"-"'&n&"~"&n+int(rslk("length"))-1&"."
						'&n&"~"&n+int(rslk("length"))-1&"."
						next   
						response.write mystr(int(ubound(mystr))-2)
					end if
				end if
				%></td>
                <td style="border-bottom:1px solid;border-right:1px solid;background:#38FF61" align="center"><%
				if ubound(mystr) >6 then
				response.write mystr(ubound(mystr)-1)  
				end if%></td>
                <td style="border-bottom:1px solid;border-right:1px solid;background:#38FF61" align="center"><%
				if ubound(mystr) >6 then
				response.write mystr(ubound(mystr)) 
				end if%></td>
                <!--td height="1" align="center">< %=trim(rs("Content"))%></td-->

              <%  
     rs.movenext
    next
   %>

 
            </table>

    