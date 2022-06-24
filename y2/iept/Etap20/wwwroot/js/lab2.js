const uri = 'api/Banks';
let banks = [];

function getBanks() {
    fetch(uri)
        .then(response => response.json())
        .then(data => _displayBanks(data))
        .catch(error => console.error('Unable to get banks.', error));
}

function addBank() {
    const addNameTextbox = document.getElementById('add-name');
    const addPhoneTextbox = document.getElementById('add-phone');
    const addAdressTextbox = document.getElementById('add-adress');

    const bank = {
        name: addNameTextbox.value.trim(),
        phoneNumber: addPhoneTextbox.value.trim(),
        adress: addAdressTextbox.value.trim(),
    };

    fetch(uri, {
        method: 'POST',
        headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(bank)
    })
        .then(response => response.json())
        .then(() => {
            getBanks();
            addNameTextbox.value = '';
            addPhoneTextbox.value = '';
            addAdressTextbox.value = '';
        })
        .catch(error => console.error('Unable to add bank.', error));
}

function deleteBank(id) {
    fetch(`${uri}/${id}`, {
        method: 'DELETE'
    })
        .then(() => getBanks())
        .catch(error => console.error('Unable to delete bank.', error));
}

function displayEditForm(id) {
    const bank = banks.find(bank => bank.bankId === id);

    document.getElementById('edit-id').value = bank.bankId;
    document.getElementById('edit-name').value = bank.name;
    document.getElementById('edit-phone').value = bank.phoneNumber;
    document.getElementById('edit-adress').value = bank.adress;
    document.getElementById('editForm').style.display = 'block';
}

function updateBank() {
    const bankId = document.getElementById('edit-id').value;
    const bank = {
        bankId: parseInt(bankId, 10),
        name: document.getElementById('edit-name').value.trim(),
        phoneNumber: document.getElementById('edit-phone').value.trim(),
        adress: document.getElementById('edit-adress').value.trim()
    };

    fetch(`${uri}/${bankId}`, {
        method: 'PUT',
        headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(bank)
    })
        .then(() => getBanks())
        .catch(error => console.error('Unable to update bank.', error));

    closeInput();

    return false;
}

function closeInput() {
    document.getElementById('editForm').style.display = 'none';
}


function _displayBanks(data) {
    const tBody = document.getElementById('banks');
    tBody.innerHTML = '';


    const button = document.createElement('button');

    data.forEach(bank => {
        let editButton = button.cloneNode(false);
        editButton.innerText = 'Edit';
        editButton.setAttribute('onclick', `displayEditForm(${bank.bankId})`);

        let deleteButton = button.cloneNode(false);
        deleteButton.innerText = 'Delete';
        deleteButton.setAttribute('onclick', `deleteBank(${bank.bankId})`);

        let tr = tBody.insertRow();


        let td1 = tr.insertCell(0);
        let textNode = document.createTextNode(bank.name);
        td1.appendChild(textNode);

        let td2 = tr.insertCell(1);
        let textNodePhone = document.createTextNode(bank.phoneNumber);
        td2.appendChild(textNodePhone);

        let td3 = tr.insertCell(2);
        let textNodeAdress = document.createTextNode(bank.adress);
        td3.appendChild(textNodeAdress);

        let td4 = tr.insertCell(3);
        td4.appendChild(editButton);

        let td5 = tr.insertCell(4);
        td5.appendChild(deleteButton);
    });

    banks = data;
}
