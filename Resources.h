const char Resource_Index[] PROGMEM = R"RES(<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>SmartBnbKit WiFi configuration</title>
        <style type="text/css">
            * {
                box-sizing: border-box;
            }
            body {
                background-color: #f3f3f4;
                font-family: "open sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
                font-size: 13px;
                color: #676a6c;
                overflow-x: hidden;
                height: 100%;
                line-height: 1.42857143;
                margin: 0;
            }
            .middle-box {
                max-width: 400px;
                z-index: 100;
                margin: 0 auto;
                padding-top: 40px;
                width: 300px;
                text-align: center;
            }
            .m-t {
                margin-top: 15px;
            }
            form {
                display: block;
                margin-top: 0em;
            }
            .form-group {
                margin-bottom: 15px;
            }
            .form-control {
                background-color: #FFFFFF;
                background-image: none;
                border: 1px solid #e5e6e7;
                border-radius: 1px;
                color: inherit;
                display: block;
                padding: 6px 12px;
                transition: border-color 0.15s ease-in-out 0s, box-shadow 0.15s ease-in-out 0s;
                width: 100%;
                font-size: 14px;
                line-height: 1.42857143;
                outline: 0;
            }
            .form-control:focus {
              border-color: #1ab394 !important;
            }
            .btn-primary:hover,
            .btn-primary:focus {
              background-color: #18a689;
              border-color: #18a689;
              color: #FFFFFF;
            }
            body.mini-navbar.fixed-sidebar .profile-element, .block {
                display: block !important;
            }
            .m-b {
                margin-bottom: 15px;
            }
            .full-width {
                width: 100% !important;
            }
            .block {
                display: block;
            }
            .btn {
                padding: 6px 12px;
                font-size: 14px;
                font-weight: 400;
                line-height: 1.42857143;
                text-align: center;
                white-space: nowrap;
                vertical-align: middle;
                touch-action: manipulation;
                cursor: pointer;
                background-image: none;
                border: 1px solid transparent;
                border-radius: 3px;
                display: block;
            }
            .btn-primary {
                background-color: #1ab394;
                border-color: #1ab394;
                color: #FFFFFF;
            }
            .logo {
                font-size: 34pt;
                font-family: sans-serif;
                color: #18a689;
            }
            .text-navy {
                color: #1ab394;
            }
            .ibox-content {
                background-color: #ffffff;
                border-color: #e7eaec;
                border-image: none;
                border-style: solid solid none;
                border-width: 1px 0px;
                margin: 10px 0;
                padding: 5px;
                color: #676a6c;
            }
            .no-margins {
                margin: 0 !important;
            }

            table {
                border-spacing: 0;
                border-collapse: collapse;
                background-color: transparent;
            }

            th, td {
                border-top: 1px solid #e7eaec;
                line-height: 1.42857;
                padding: 8px;
                vertical-align: middle;
            }
            .table>thead:first-child>tr:first-child>td, .table>thead:first-child>tr:first-child>th {
                border-top: 0;
            }
            th {
                text-align: left;
                border-bottom: 1px solid #DDDDDD;
                vertical-align: bottom;
            }
            .loader {
                -webkit-animation: spin 1s linear infinite;
                -moz-animation: spin 1s linear infinite;
                animation: spin 1s linear infinite;
            }
            @-moz-keyframes spin { 100% { -moz-transform: rotate(360deg); } }
            @-webkit-keyframes spin { 100% { -webkit-transform: rotate(360deg); } }
            @keyframes spin { 100% { -webkit-transform: rotate(360deg); transform: rotate(360deg); } }
        </style>
        <script type="text/javascript">
            function post(url, data, callback) {
                var http = new XMLHttpRequest();
                http.onreadystatechange = function() {
                    if (this.readyState == 4 && callback)
                        callback(this.responseText);
                };
                http.open('POST', url, true);
                http.timeout = 60000;
                http.send(data);
            }
            function save() {
                var ssid = document.getElementById('ssid').value;
                var pass = document.getElementById('password').value;
                var api_login = document.getElementById('api_login').value;
                var api_pass = document.getElementById('api_pass').value;
                
                post('/save', 'ssid=' + encodeURIComponent(ssid) +
                              '&password=' + encodeURIComponent(pass) +
                              '&api_login=' + encodeURIComponent(api_login) +
                              '&api_pass=' + encodeURIComponent(api_pass), function(resp) {
                    alert('Saved ' + resp); // Todo: make this pretty
                    window.close();
                });
            }
            
            post('/scan', '', function (data) {
                var html = '';
                var results = JSON.parse(data);
                if (!data || !results) {
                    html = '<tr><td colspan="2" valign="middle" align="center">No networks found. Refresh to scan again.</td></tr>';
                } else {
                    for (var i in results) {
                        var lock = !results[i].open? '<div style="position: absolute; left: 3px;"><svg width="14" height="14" viewBox="0 0 1792 1792" xmlns="http://www.w3.org/2000/svg"><path d="M640 768h512v-192q0-106-75-181t-181-75-181 75-75 181v192zm832 96v576q0 40-28 68t-68 28h-960q-40 0-68-28t-28-68v-576q0-40 28-68t68-28h32v-192q0-184 132-316t316-132 316 132 132 316v192h32q40 0 68 28t28 68z" fill="#000"/></svg></div>' : '';
                        
                        html += '<tr onclick="document.getElementById(\'ssid\').value = this.getElementsByTagName(\'td\')[0].getElementsByTagName(\'span\')[0].innerHTML" style="cursor: pointer;"> \
                                    <td style="position: relative">' + lock + '<span>' + results[i].ssid + '</span></td> \
                                    <td class="text-navy"><svg width="14" height="14" viewBox="0 0 1792 1792" xmlns="http://www.w3.org/2000/svg"><path d="M896 1523q-20 0-93-73.5t-73-93.5q0-32 62.5-54t103.5-22 103.5 22 62.5 54q0 20-73 93.5t-93 73.5zm270-271q-2 0-40-25t-101.5-50-128.5-25-128.5 25-101 50-40.5 25q-18 0-93.5-75t-75.5-93q0-13 10-23 78-77 196-121t233-44 233 44 196 121q10 10 10 23 0 18-75.5 93t-93.5 75zm273-272q-11 0-23-8-136-105-252-154.5t-268-49.5q-85 0-170.5 22t-149 53-113.5 62-79 53-31 22q-17 0-92-75t-75-93q0-12 10-22 132-132 320-205t380-73 380 73 320 205q10 10 10 22 0 18-75 93t-92 75zm271-271q-11 0-22-9-179-157-371.5-236.5t-420.5-79.5-420.5 79.5-371.5 236.5q-11 9-22 9-17 0-92.5-75t-75.5-93q0-13 10-23 187-186 445-288t527-102 527 102 445 288q10 10 10 23 0 18-75.5 93t-92.5 75z" fill="#1ab394" /></svg> ' + results[i].strength +'%</td> \
                                </tr>';
                    }
                }
                document.getElementById('scan_results').innerHTML = html;
            });
        </script>
    </head>
    <body>
        <div class="middle-box">
            <div>
                <div class="logo">SmartBnbKit</div>
                <p style="margin-top: -5px;">WiFi configuration</p>
                
                <div class="ibox-content">
                    <table class="table table-hover no-margins full-width">
                        <thead>
                        <tr>
                            <th>SSID</th>
                            <th>Signal strength</th>
                        </tr>
                        </thead>
                        <tbody id="scan_results">
                            <tr><td colspan="2" valign="middle" align="center">
                                <svg class="loader" width="32" height="32" viewBox="0 0 100 100" xmlns="http://www.w3.org/2000/svg" preserveAspectRatio="xMidYMid"><path d="M10,50c0,0,0,0.5,0.1,1.4c0,0.5,0.1,1,0.2,1.7c0,0.3,0.1,0.7,0.1,1.1c0.1,0.4,0.1,0.8,0.2,1.2c0.2,0.8,0.3,1.8,0.5,2.8 c0.3,1,0.6,2.1,0.9,3.2c0.3,1.1,0.9,2.3,1.4,3.5c0.5,1.2,1.2,2.4,1.8,3.7c0.3,0.6,0.8,1.2,1.2,1.9c0.4,0.6,0.8,1.3,1.3,1.9 c1,1.2,1.9,2.6,3.1,3.7c2.2,2.5,5,4.7,7.9,6.7c3,2,6.5,3.4,10.1,4.6c3.6,1.1,7.5,1.5,11.2,1.6c4-0.1,7.7-0.6,11.3-1.6 c3.6-1.2,7-2.6,10-4.6c3-2,5.8-4.2,7.9-6.7c1.2-1.2,2.1-2.5,3.1-3.7c0.5-0.6,0.9-1.3,1.3-1.9c0.4-0.6,0.8-1.3,1.2-1.9 c0.6-1.3,1.3-2.5,1.8-3.7c0.5-1.2,1-2.4,1.4-3.5c0.3-1.1,0.6-2.2,0.9-3.2c0.2-1,0.4-1.9,0.5-2.8c0.1-0.4,0.1-0.8,0.2-1.2 c0-0.4,0.1-0.7,0.1-1.1c0.1-0.7,0.1-1.2,0.2-1.7C90,50.5,90,50,90,50s0,0.5,0,1.4c0,0.5,0,1,0,1.7c0,0.3,0,0.7,0,1.1 c0,0.4-0.1,0.8-0.1,1.2c-0.1,0.9-0.2,1.8-0.4,2.8c-0.2,1-0.5,2.1-0.7,3.3c-0.3,1.2-0.8,2.4-1.2,3.7c-0.2,0.7-0.5,1.3-0.8,1.9 c-0.3,0.7-0.6,1.3-0.9,2c-0.3,0.7-0.7,1.3-1.1,2c-0.4,0.7-0.7,1.4-1.2,2c-1,1.3-1.9,2.7-3.1,4c-2.2,2.7-5,5-8.1,7.1 c-0.8,0.5-1.6,1-2.4,1.5c-0.8,0.5-1.7,0.9-2.6,1.3L66,87.7l-1.4,0.5c-0.9,0.3-1.8,0.7-2.8,1c-3.8,1.1-7.9,1.7-11.8,1.8L47,90.8 c-1,0-2-0.2-3-0.3l-1.5-0.2l-0.7-0.1L41.1,90c-1-0.3-1.9-0.5-2.9-0.7c-0.9-0.3-1.9-0.7-2.8-1L34,87.7l-1.3-0.6 c-0.9-0.4-1.8-0.8-2.6-1.3c-0.8-0.5-1.6-1-2.4-1.5c-3.1-2.1-5.9-4.5-8.1-7.1c-1.2-1.2-2.1-2.7-3.1-4c-0.5-0.6-0.8-1.4-1.2-2 c-0.4-0.7-0.8-1.3-1.1-2c-0.3-0.7-0.6-1.3-0.9-2c-0.3-0.7-0.6-1.3-0.8-1.9c-0.4-1.3-0.9-2.5-1.2-3.7c-0.3-1.2-0.5-2.3-0.7-3.3 c-0.2-1-0.3-2-0.4-2.8c-0.1-0.4-0.1-0.8-0.1-1.2c0-0.4,0-0.7,0-1.1c0-0.7,0-1.2,0-1.7C10,50.5,10,50,10,50z" fill="#1ab394"></svg>
                            </td></tr>
                        </tbody>
                    </table>
                </div>

                <h3>Please enter your WiFi credentials</h3>
                <form class="m-t" method="post">
                    <div class="form-group"><input type="text" class="form-control" placeholder="SSID" required name="ssid" id="ssid" value="%ssid%"></div>
                    <div class="form-group"><input type="password" class="form-control" placeholder="Password" id="password" value="%pass%"> </div>
                    <h3>Your API credentials:</h3>
                    <div class="form-group"><input type="text" class="form-control" placeholder="API username" required id="api_login" value="%api_login%"></div>
                    <div class="form-group"><input type="password" class="form-control" placeholder="API password" required id="api_pass" value="%api_pass%"> </div>
                    <button onclick="save()" class="btn btn-primary block full-width m-b">Save and reboot</button>
                </form>
                <p class="m-t"> <small>Toptal © 2016</small> </p>
            </div>
        </div>
    </body>
</html>)RES";
