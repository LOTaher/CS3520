### Class Name: Account
#### Responsibilities:
- Manage user account details.
- Authenticate user password.
- Provide associated customer details.

#### Collaborators:
- Customer


### Class Name: Customer
#### Responsibilities:
- Manage customer details.
- Access and modify the customer's favorite list.

#### Collaborators:
- FavoriteList


### Class Name: Dealership
#### Responsibilities:
- Manage dealership details.
- Manage inventory.
- Place orders.

#### Collaborators:
- Inventory
- Order


### Class Name: Delivery
#### Responsibilities:
- Manage delivery method details.
- Manage delivery address.

#### Collaborators:
- None


### Class Name: FavoriteList
#### Responsibilities:
- Manage the list of favorite vehicles.
- Add and remove vehicles from the list.
- Provide access to all favorite vehicles.

#### Collaborators:
- Vehicle


### Class Name: Inventory
#### Responsibilities:
- Manage the list of vehicles in inventory.
- Add and remove vehicles from inventory.
- Find vehicles in inventory.
- Provide access to all vehicles in inventory.

#### Collaborators:
- Vehicle


### Class Name: OnlineDealership
#### Responsibilities:
- Manage online dealership details.
- Access website information.

#### Collaborators:
- None (inherits from Dealership)


### Class Name: Order
#### Responsibilities:
- Manage order details.
- Provide associated vehicle, customer, and delivery details.

#### Collaborators:
- Vehicle
- Customer
- Delivery


### Class Name: PhysicalDealership
#### Responsibilities:
- Manage physical dealership details.
- Access physical address information.

#### Collaborators:
- None (inherits from Dealership)


### Class Name: Vehicle
#### Responsibilities:
- Manage vehicle details.

#### Collaborators:
- None




