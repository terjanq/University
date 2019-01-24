<?php

if(!isset($_GET['q'])){
    die("?q=QUERY");
}

$FLAG = "flag{This_is_a_super_secret_flag}";

$q = $_GET['q'];
$q_enc = htmlspecialchars($q, ENT_QUOTES);
$error = "<h1>Results for <strong>$q_enc</strong> not found </h1>";
$js = "
<script>
(()=>{
  for (let pre of document.getElementsByTagName('pre')) {
    let text = pre.innerHTML;
    let q = '$q_enc';
    let idx = text.indexOf(q);
    pre.innerHTML = `\${text.substr(0, idx)}<mark>\${q}</mark>\${text.substr(idx+q.length)}`;
  }
})();
</script>
";

$found = "<h1>Flag</h1><pre>$FLAG</pre>$js";


if(strpos($FLAG, $q) === false){
    die($error);
}

die($found);

?>